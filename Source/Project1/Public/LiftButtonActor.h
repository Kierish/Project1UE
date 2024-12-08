// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiftButtonActor.generated.h"

class ALift;
class UStaticMeshComponent;
class AMainCharacter;
UCLASS()
class PROJECT1_API ALiftButtonActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    ALift* Lift;
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Button;

    ALiftButtonActor();

    void OnInteract();

protected:
    UPROPERTY(EditAnywhere)
    bool bIsOnTop = false;
};
