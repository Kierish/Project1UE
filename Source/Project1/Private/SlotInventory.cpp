// Copyright Kierish. All rights reserved

#include "SlotInventory.h"
#include "Components/TextBlock.h"
#include "SlotInventory.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"


void USlotInventory::ChangeBrushColor(bool bIsSlotSelected)
{
    if (bIsSlotSelected)
    {
        BorderSlot->SetBrushColor(BorderColorSelected);
    }
    else
    {
        BorderSlot->SetBrushColor(BorderColor);
    }
}

void USlotInventory::SetImage(UTexture2D* Image)
{
    if (ItemImage && Image)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Image);
        ItemImage->SetBrush(Brush);
        ItemImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USlotInventory::RemoveImage()
{
    if (ItemImage)
    {
        ItemImage->SetVisibility(ESlateVisibility::Hidden);
        ItemImage->SetBrushFromTexture(nullptr); 
    }
}

void USlotInventory::NativeConstruct()
{
    Super::NativeConstruct();
    if (Index)
    {
        Index->SetText(FText::FromString(FString::FromInt(SlotNum)));
    }
    if (bIsSelected)
    {
        BorderSlot->SetBrushColor(BorderColorSelected);
    }
}
