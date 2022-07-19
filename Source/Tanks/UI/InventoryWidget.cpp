// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::Init(int32 ItemsNum)
{
	if (ItemCellsGrid)
    {
	    ItemCellsGrid->ClearChildren();
	    for (int32 i = 0; i < ItemsNum; i++)
	    {
		    UInventoryCellWidget * Widget = CreateCellWidget();
		    Widget->IndexInInventory = i;
		    ItemCellsGrid->AddChildToUniformGrid(Widget,i / ItemsInPow, i % ItemsInPow);
	    }
    }

}

bool UInventoryWidget::AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo, int32 SlotPosition)
{
	if (ItemInfo.Type == EItemType::IT_Currency) //it's inventory
	{
		if (GoldCell)
		{
			return GoldCell->AddItem(Item, ItemInfo);
		}
		return false;
	}
	if (ItemCellsGrid)
	{
		
		UInventoryCellWidget * WidgetToAddItem = nullptr;
		UInventoryCellWidget ** WidgetToAddItemPtr = 
		CellWidgets.FindByPredicate([SlotPosition](UInventoryCellWidget * Widget)
		{
		return Widget && Widget->IndexInInventory == SlotPosition;
		});
		if (WidgetToAddItemPtr)
		{
			WidgetToAddItem = *WidgetToAddItemPtr;
			
		}
		else
		{
			for (UInventoryCellWidget * CellWidget : CellWidgets)
			{
				if (!CellWidget->HasItem())
				{
					WidgetToAddItem = CellWidget;					
					break;
				}
			}
		}
		if (WidgetToAddItem)
		{
			return WidgetToAddItem->AddItem(Item, ItemInfo);
		}		
	}	
	return false;
}

UInventoryCellWidget* UInventoryWidget::CreateCellWidget()
{
	if (CellWidgetClass)
	{
		UInventoryCellWidget * CellWidget = CreateWidget<UInventoryCellWidget>(this,CellWidgetClass);
		CellWidgets.Add(CellWidget);
		return CellWidget;
	}
	return nullptr;
}
