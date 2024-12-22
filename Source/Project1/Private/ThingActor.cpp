// Copyright Kierish. All rights reserved

#include "ThingActor.h"
#include "Components/SphereComponent.h"
#include "MainCHaracter.h"
#include "Blueprint/UserWidget.h"

AThingActor::AThingActor()
{
    PrimaryActorTick.bCanEverTick = true;
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    RootComponent = SphereCollision;

    Thing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thing"));
    Thing->SetupAttachment(SphereCollision);
}
void AThingActor::BeginPlay()
{
    Super::BeginPlay();
    SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AThingActor::OnBeginOverlap);
    SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AThingActor::OnEndOverlap);
}

void AThingActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
    AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
    if (Character && Thing)
    {
        Character->SetVisibilityTextInteract(true);
        Thing->SetOverlayMaterial(OverlayMaterial);
    }
    if (Character)
    {
        for (int i = 0; i < Character->SlotsCount; i++)
        {
            if (Character->Things[i] == nullptr)
            {
                Character->Things[i] = this;
                index = i;
                break;
            }
        }
    }
}

void AThingActor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
    AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
    if (Character && Thing)
    {
        bool bOtherThings = false;
        for (int i = 0; i < Character->SlotsCount; i++)
        {
            if (Character->Things[i] != nullptr && i != index)
            {
                bOtherThings = true;
                break;
            }
        }
        if (!bOtherThings)
        {
            Character->SetVisibilityTextInteract(false);
        }
        Thing->SetOverlayMaterial(nullptr);
    }
    if (Character)
    {
        if (Character->Things[index])
        {
            Character->Things[index] = nullptr;
        }  
        index = -1;
    }
}

void AThingActor::OnInteract(AMainCharacter* Character)
{
    if (bIsInInventory)
    {
        bool bOtherThings = false;
        for (int i = 0; i < Character->SlotsCount; i++)
        {
            if (Character->Things[i] != nullptr)
            {
                bOtherThings = true;
                break;
            }
        }
        if (!bOtherThings)
        {
            UE_LOG(LogTemp, Warning, TEXT("!bOtherThings"));
            Thing->SetOverlayMaterial(nullptr);
            Character->SetVisibilityTextInteract(false);
        }
    }
}
