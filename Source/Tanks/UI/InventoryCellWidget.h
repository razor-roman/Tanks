// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItemInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryCellWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	bool HasItem() { return bHasItem; }
	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo);
	void Clear();
	const FInventorySlotInfo& GetItem();
	int32 IndexInInventory = -1;
protected:
	bool bHasItem;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* ItemImage;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CountText;
	UPROPERTY()
	FInventorySlotInfo StoredItem;
};
