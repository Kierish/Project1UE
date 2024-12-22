// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotInventory.generated.h"

class UImage;
class UTextBlock;
class UBorder;
UCLASS()
class PROJECT1_API USlotInventory : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UImage* ItemImage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTextBlock* Index;
    UPROPERTY(EditAnywhere)
    UBorder* BorderSlot;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int SlotNum = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSelected = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor BorderColor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor BorderColorSelected;

    void ChangeBrushColor(bool bIsSlotSelected);
    void SetImage(UTexture2D* Image);
    void RemoveImage();

protected:
    virtual void NativeConstruct() override;
};
