

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class UCharacterWidget;
class AThingActor;
UCLASS()
class PROJECT1_API AMainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCharacterWidget* Widget;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    TArray<AThingActor*> Inventory;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    TArray<AThingActor*> Things;
    UPROPERTY(EditAnywhere)
    int SlotsCount = 5;
    bool bIsOverlapThing = false;
    AMainCharacter();
    void SetVisibilityTextInteract(bool bVisibility);

protected:
    UPROPERTY(VisibleAnywhere)
    UCameraComponent *Camera;

    UPROPERTY(EditAnywhere)
    float InteractLineTraceLength = 350.f;
    UPROPERTY(EditAnywhere)
    float StrengthThrow = 1000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ChooseThing = 0;

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveForwardBackward(float Value);
    void MoveRightLeft(float Value);
    void Jump();
    void StopJump();
    void Interact();
    void RemoveThing();
    void SelectThingNum(float Value);
    void Selecting(int PreviousThing);
    UFUNCTION()
    void ChoosingThing(float Value);
};
