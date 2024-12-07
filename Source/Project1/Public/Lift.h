// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Lift.generated.h"

class UStaticMeshComponent;
class AMainCharacter;
UCLASS()
class PROJECT1_API ALift : public AActor
{
	GENERATED_BODY()
	
public:	
    UPROPERTY(EditAnywhere)
    AMainCharacter* Character;
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Button;

	ALift();

   virtual void Tick(float DeltaTime) override;
   void OnInteract();

protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Platform;
    FTimeline Timeline;
    UPROPERTY(EditAnywhere)
    UCurveFloat* CurveFloat;

    UPROPERTY(EditAnywhere)
    float Height = 12.f;
    UPROPERTY(EditAnywhere)
    float Distance;

    FVector StartLocation;
    FTimerHandle TimerHandle;
    bool bIsOnTop = false;
    bool bIsMoving = false;
    UFUNCTION()
    void Move(float Value);
    virtual void BeginPlay() override;
    void OnMovementComplete();
};
