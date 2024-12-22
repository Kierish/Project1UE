// Copyright Kierish. All rights reserved


#include "CharacterWidget.h"
#include "Components/VerticalBox.h"
#include "Components/UniformGridPanel.h"
#include "SlotInventory.h"
#include "Engine/Texture2D.h"



void UCharacterWidget::SetVisibilityInteractionText(bool bVisibility)
{
    if (!Interaction)
    {
        UE_LOG(LogTemp, Warning, TEXT("sdfasdf"));
    }
    if (bVisibility)
    {
        Interaction->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        Interaction->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCharacterWidget::ChooseSlot(int Index, int PreviousIndex)
{
    USlotInventory* SelectedSlot = Cast<USlotInventory>(InventorySlot->GetChildAt(Index));
    USlotInventory* PreviousSlot = Cast<USlotInventory>(InventorySlot->GetChildAt(PreviousIndex));
    if (SelectedSlot && PreviousSlot)
    {
        SelectedSlot->bIsSelected = true;
        SelectedSlot->ChangeBrushColor(SelectedSlot->bIsSelected);
        PreviousSlot->bIsSelected = false;
        PreviousSlot->ChangeBrushColor(PreviousSlot->bIsSelected);
    }
}

void UCharacterWidget::SetItemImage(int Index, UTexture2D* Image)
{
    USlotInventory* SlotItem = Cast<USlotInventory>(InventorySlot->GetChildAt(Index));
    if (SlotItem)
    {
        SlotItem->SetImage(Image);
    }
}

void UCharacterWidget::RemoveImage(int Index)
{
    USlotInventory* SlotItem = Cast<USlotInventory>(InventorySlot->GetChildAt(Index));
    if (SlotItem)
    {
        SlotItem->RemoveImage();
    }
}
