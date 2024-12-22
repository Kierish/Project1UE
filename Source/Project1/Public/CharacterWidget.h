// Copyright Kierish. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

class UVerticalBox;
class UUniformGridPanel;
class UTexture2D;
UCLASS()
class PROJECT1_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetVisibilityInteractionText(bool bVisibility);

    UPROPERTY(EditAnywhere)
    UVerticalBox* Interaction;
    UPROPERTY(EditAnywhere)
    UUniformGridPanel* InventorySlot; 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int NumSelectedSlot;

    void ChooseSlot(int Index, int PreviousIndex);
    void SetItemImage(int Index, UTexture2D* Image);
    void RemoveImage(int Index);
};
