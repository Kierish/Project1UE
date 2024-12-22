// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThingActor.generated.h"

class AMainCharacter;
class USphereComponent;
class UStaticMeshComponent;
class UMaterial;
class UTexture2D;
UCLASS()
class PROJECT1_API AThingActor : public AActor
{
	GENERATED_BODY()
	
public:	
    UPROPERTY(EditAnywhere)
    USphereComponent* SphereCollision; 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Thing;
    UPROPERTY(EditAnywhere)
    UTexture2D* ItemImage;
    bool bIsInInventory = false;
	AThingActor();
    void OnInteract(AMainCharacter* Character);
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

    UPROPERTY(EditAnywhere)
    UMaterial* OverlayMaterial;
    int index = -1;
	virtual void BeginPlay() override;
    
    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       int32 OtherBodyIndex);
};
