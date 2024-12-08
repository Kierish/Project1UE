

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "DoorActor.h"
#include "Lift.h"
#include "LiftButtonActor.h"
#include "DrawDebugHelpers.h"

AMainCharacter::AMainCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    Camera->SetupAttachment(GetCapsuleComponent());
    Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
    Camera->bUsePawnControlRotation = true;
}

void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (Widget)
    {
        Widget->AddToViewport();
    }
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainCharacter::MoveRightLeft);

    PlayerInputComponent->BindAxis("LookX", this, &AMainCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookY", this, &AMainCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
    PlayerInputComponent->BindAction("StopJump", IE_Released, this, &AMainCharacter::Jump);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
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

    ADoorActor *Door = Cast<ADoorActor>(HitResult.GetActor());
    if (Door)
    {
        Door->Character = this;
        Door->OnInteract();
    }
    ALift* Lift = Cast<ALift>(HitResult.GetActor());
    if (Lift && (HitResult.GetComponent() == Lift->Button || HitResult.GetComponent()->IsAttachedTo(Lift->Button)))
    {
        Lift->OnInteract();
    }
    ALiftButtonActor* Button = Cast<ALiftButtonActor>(HitResult.GetActor());
    if (Button)
    {
        Button->OnInteract();
    }
}
