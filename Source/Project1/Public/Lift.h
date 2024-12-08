// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Lift.generated.h"

class UStaticMeshComponent;
class AMainCharacter;
class UMaterial;
UCLASS()
class PROJECT1_API ALift : public AActor
{
	GENERATED_BODY()
	
public:	
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Button;

   
    bool bIsOnTop = false;
	
    ALift();

   virtual void Tick(float DeltaTime) override;
   void OnInteract();
   
protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Platform;
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* ButtonGlow;
    FTimeline Timeline;
    UPROPERTY(EditAnywhere)
    UCurveFloat* CurveFloat;
    UPROPERTY(EditAnywhere)
    UMaterial* StopMaterial;
    UPROPERTY(EditAnywhere)
    UMaterial* MovingMaterial;
    UPROPERTY(EditAnywhere)
    float Height = 12.f;
    UPROPERTY(EditAnywhere)
    float Distance;

    FVector StartLocation;
    FTimerHandle TimerHandle;
    bool bIsMoving = false;
    UFUNCTION()
    void Move(float Value);
    virtual void BeginPlay() override;
    void OnMovementComplete();
};
