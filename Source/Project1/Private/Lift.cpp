// Copyright Kierish. All rights reserved

#include "Lift.h"
#include "MainCHaracter.h"

ALift::ALift()
{
    PrimaryActorTick.bCanEverTick = true;

    Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
    Platform->SetupAttachment(RootComponent);

    Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
    Button->SetupAttachment(Platform);
}

void ALift::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Timeline.TickTimeline(DeltaTime);
}

void ALift::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = Platform->GetRelativeLocation();
    if (CurveFloat)
    {
        FOnTimelineFloat TimelineProgress;
        TimelineProgress.BindDynamic(this, &ALift::Move);
        Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
    }
}

void ALift::OnInteract()
{
    if (bIsMoving)
    {
        return;
    }
    bIsMoving = true;
    if (!bIsOnTop)
    {
        Timeline.Play();
    }
    else
    {
        Timeline.Reverse();
    }
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALift::OnMovementComplete, Timeline.GetTimelineLength() + 0.1f, false);
}
void ALift::OnMovementComplete()
{
    bIsMoving = false;
    bIsOnTop = !bIsOnTop;
}
void ALift::Move(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Move"));

    if (!bIsOnTop)
    {
        StartLocation.Z += Value * Height;
    }
    else
    {
        StartLocation.Z -= (1.0f - Value) * Height;
    }

    Platform->SetRelativeLocation(StartLocation);
    UE_LOG(LogTemp, Warning, TEXT("PlatformMove"));
}
