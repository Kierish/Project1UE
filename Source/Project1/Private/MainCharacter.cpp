

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DoorActor.h"
#include "Lift.h"
#include "LiftButtonActor.h"
#include "ThingActor.h"
#include "DrawDebugHelpers.h"

AMainCharacter::AMainCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    Camera->SetupAttachment(GetCapsuleComponent());
    Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
    Camera->bUsePawnControlRotation = true;

    Widget = CreateDefaultSubobject<UCharacterWidget>(TEXT("Widget"));

    Inventory.Init(nullptr, SlotsCount);
    Things.Init(nullptr, SlotsCount);
}



void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(Widget);
    Widget->AddToViewport();
}

void AMainCharacter::SetVisibilityTextInteract(bool bVisibility)
{
    Widget->SetVisibilityInteractionText(bVisibility);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *UEnum::GetValueAsString(Widget->GetVisibility()));
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainCharacter::MoveRightLeft);

    PlayerInputComponent->BindAxis("LookX", this, &AMainCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookY", this, &AMainCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("ChoosingThing", this, &AMainCharacter::ChoosingThing);

    PlayerInputComponent->BindAxis("SelectThingNum", this, &AMainCharacter::SelectThingNum);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
    PlayerInputComponent->BindAction("StopJump", IE_Released, this, &AMainCharacter::Jump);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
    PlayerInputComponent->BindAction("RemoveThing", IE_Pressed, this, &AMainCharacter::RemoveThing);
}

void AMainCharacter::MoveForwardBackward(float Value)
{
    if (Value != 0.0f)
    {
        FVector Direction = GetActorForwardVector();
        AddMovementInput(Direction, Value);
    }
}

void AMainCharacter::MoveRightLeft(float Value)
{
    if (Value != 0.0f)
    {
        FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, Value);
    }
}

void AMainCharacter::Jump()
{
    bPressedJump = true;
}

void AMainCharacter::StopJump()
{
    bPressedJump = false;
}

void AMainCharacter::Interact()
{
    if (Camera == nullptr)
        return;

    FHitResult HitResult;
    FVector Start = Camera->GetComponentLocation();
    FVector End = Start + Camera->GetForwardVector() * 350.f;

    GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
    DrawDebugPoint(GetWorld(), End, 20.f, FColor::Red, false, 2.f);
    DrawDebugPoint(GetWorld(), Start, 20.f, FColor::Blue, false, 2.f);

    ADoorActor* Door = Cast<ADoorActor>(HitResult.GetActor());
    if (Door)
    {
        Door->Character = this;
        Door->OnInteract();
        return;
    }
    ALift* Lift = Cast<ALift>(HitResult.GetActor());
    if (Lift && (HitResult.GetComponent() == Lift->Button || HitResult.GetComponent()->IsAttachedTo(Lift->Button)))
    {
        Lift->OnInteract();
        return;
    }
    ALiftButtonActor* Button = Cast<ALiftButtonActor>(HitResult.GetActor());
    if (Button)
    {
        Button->OnInteract();
        return;
    }
    for (int i = 0; i < SlotsCount; i++)
    {
        if (Things[i])
        {
            bIsOverlapThing = true;
            break;
        }
    }
    if (bIsOverlapThing)
    {
        for (int i = 0; i < SlotsCount; i++)
        {
            if (Things[i])
            {
                for (int j = 0; j < SlotsCount; j++)
                {
                    if (Inventory[ChooseThing] == nullptr)
                    {
                        Inventory[ChooseThing] = Things[i];
                        Things[i] = nullptr;
                        Widget->SetItemImage(ChooseThing, Inventory[ChooseThing]->ItemImage);
                        Inventory[ChooseThing]->SphereCollision->SetSimulatePhysics(false);
                        Inventory[ChooseThing]->AttachToComponent(Camera, FAttachmentTransformRules::KeepWorldTransform);
                        Inventory[ChooseThing]->SetActorRelativeLocation(FVector(50.f, 25.f, -15.f));
                        Inventory[ChooseThing]->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
                        Inventory[ChooseThing]->bIsInInventory = true;
                        Inventory[ChooseThing]->OnInteract(this);
                        Inventory[ChooseThing]->SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                        break;
                    }
                    else if (Inventory[j] == nullptr)
                    {
                        Inventory[j] = Things[i];
                        Things[i] = nullptr;
                        Widget->SetItemImage(j, Inventory[ChooseThing]->ItemImage);
                        Inventory[j]->SetActorHiddenInGame(true);
                        Inventory[j]->SphereCollision->SetSimulatePhysics(false);
                        Inventory[j]->SetActorLocation(FVector(50.f, 25.f, -15.f));
                        Inventory[j]->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
                        Inventory[j]->bIsInInventory = true;
                        Inventory[j]->OnInteract(this);
                        Inventory[j]->SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                        break;
                    }
                }
                break;
            }        
        }
        bIsOverlapThing = false;
    }
}

void AMainCharacter::RemoveThing()
{
    if (Inventory[ChooseThing])
    {
        if (Inventory[ChooseThing]->bIsInInventory)
        {
            Widget->RemoveImage(ChooseThing);
            Inventory[ChooseThing]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            Inventory[ChooseThing]->SphereCollision->SetSimulatePhysics(true);
            Inventory[ChooseThing]->SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            FVector ThrowDiraction = Camera->GetForwardVector();
            Inventory[ChooseThing]->SphereCollision->AddImpulse(ThrowDiraction * StrengthThrow, NAME_None, true);
            Inventory[ChooseThing]->bIsInInventory = false;
            Inventory[ChooseThing] = nullptr;
        }           
    }
}

void AMainCharacter::ChoosingThing(float Value)
{
    if ((int)Value != 0)
    {
        int PreviousThing = ChooseThing;
        ChooseThing = (ChooseThing + (int)Value) % SlotsCount;
        if (ChooseThing < 0)
        {
            ChooseThing = SlotsCount - 1;
        }
        Selecting(PreviousThing);
    }
}

void AMainCharacter::SelectThingNum(float Value)
{
    if (ChooseThing != (int)Value - 1 && (int)Value != 0 && (int)Value <= SlotsCount)
    {
        int PreviousThing = ChooseThing;
        ChooseThing = (int)Value - 1;
        Selecting(PreviousThing);
    }
}

void AMainCharacter::Selecting(int PreviousThing)
{
    Widget->ChooseSlot(ChooseThing, PreviousThing);
    if (Inventory[PreviousThing])
    {
        Inventory[PreviousThing]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Inventory[PreviousThing]->SetActorHiddenInGame(true);
        Inventory[PreviousThing]->SetActorLocation(FVector(50.f, 25.f, -15.f));
    }
    if (Inventory[ChooseThing])
    {
        Inventory[ChooseThing]->SetActorHiddenInGame(false);
        Inventory[ChooseThing]->AttachToComponent(Camera, FAttachmentTransformRules::KeepWorldTransform);
        Inventory[ChooseThing]->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
        Inventory[ChooseThing]->SetActorRelativeLocation(FVector(50.f, 25.f, -15.f));
    }
}
