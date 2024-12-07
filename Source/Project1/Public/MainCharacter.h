

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class UUserWidget;
UCLASS()
class PROJECT1_API AMainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMainCharacter();

protected:
    UPROPERTY(VisibleAnywhere)
    UCameraComponent *Camera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
    UUserWidget* Widget;

    UPROPERTY(EditAnywhere)
    float InteractLineTraceLength = 350.f;
    
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveForwardBackward(float Value);
    void MoveRightLeft(float Value);
    void Jump();
    void StopJump();
    void Interact();
};
