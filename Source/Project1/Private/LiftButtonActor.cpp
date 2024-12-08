// Copyright Kierish. All rights reserved

#include "LiftButtonActor.h"
#include "Lift.h"
#include "MainCHaracter.h"

ALiftButtonActor::ALiftButtonActor()
{
    PrimaryActorTick.bCanEverTick = true;
    Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
    Button->SetupAttachment(RootComponent);
}

void ALiftButtonActor::OnInteract()
{
    if (Lift->bIsOnTop != bIsOnTop)
    {
        Lift->OnInteract();
    }
}
