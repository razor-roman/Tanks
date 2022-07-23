// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInventoryItemInfo.h"
#include "InventoryCellWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnItemDrop OnItemDrop;
    virtual void NativeConstruct() override;
    void Init(int32 ItemsNum);
    bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo,int32 SlotPosition = -1);
protected:
	void OnItemDropped(UInventoryCellWidget * DraggedFrom,UInventoryCellWidget * DroppedTo);
	UPROPERTY(meta = (BindWidgetOptional))
	UUniformGridPanel* ItemCellsGrid;
	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInPow = 5;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;
	UPROPERTY()
	TArray<UInventoryCellWidget*> CellWidgets;
	UPROPERTY(meta = (BindWidgetOptional))
	UInventoryCellWidget* GoldCell;
	UInventoryCellWidget * CreateCellWidget();
};
