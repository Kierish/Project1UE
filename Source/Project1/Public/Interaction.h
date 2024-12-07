

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction.generated.h"

UCLASS()
class PROJECT1_API AInteraction : public AActor
{
	GENERATED_BODY()
	
public:	

	AInteraction();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
