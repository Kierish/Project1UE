
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DoorActor.generated.h"


class AMainCharacter;
class UStaticMeshComponent;
UCLASS()
class PROJECT1_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
    AMainCharacter* Character;

	ADoorActor();

	virtual void Tick(float DeltaTime) override;
    void OnInteract();


protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Door;
    
	FTimeline Timeline;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	bool bIsDoorClosed = true;
    bool bDoorOnSameSide;


	UPROPERTY(EditAnywhere)
	float DoorRotateAngle = 90.f;

	UFUNCTION()
	void OpenDoor(float Value);

	virtual void BeginPlay() override;

	void SetDoorOnSameSide();
};
