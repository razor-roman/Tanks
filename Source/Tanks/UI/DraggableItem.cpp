// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"

#include "FruitDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TankText)
	    {
	    TankText->SetText(TankName);
	    }
}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{	
	if(Cast<UVerticalBox>(GetParent()) && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
	}
	return  FReply::Handled();
}

void UDraggableItem::RestoreVisuals(UDragDropOperation* Operation)
{
	if(UDraggableItem* Item = Cast<UDraggableItem>(Operation->DefaultDragVisual))
	{
		Item->SetColorAndOpacity(FLinearColor(1,1,1,1));
		Item->SetVisibility(ESlateVisibility::Visible);
	}
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UFruitDragDropOperation::StaticClass());
	UFruitDragDropOperation* TankOperation = Cast<UFruitDragDropOperation>(OutOperation);
	if(TankOperation)
	{
		TankOperation->DefaultDragVisual = this;
		SetColorAndOpacity(FLinearColor(1,1,1,0.7));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		TankOperation->OnDragCancelled.AddDynamic(this,&ThisClass::RestoreVusuals);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UVerticalBox* VerticalBox = Cast<UVerticalBox>(GetParent());
	UFruitDragDropOperation* TankOperation = Cast<UFruitDragDropOperation>(InOperation);
	if(VerticalBox&&TankOperation&&TankOperation->DefaultDragVisual&&this!=TankOperation->DefaultDragVisual)
	{
		const int32 OverIndex = VerticalBox->GetChildIndex(TankOperation->DefaultDragVisual);

		if(OverIndex>=0)
		{
			VerticalBox->RemoveChildAt(OverIndex);

			const TArray<UWidget*> Children = VerticalBox->GetAllChildren();
			VerticalBox->ClearChildren();
			
			for(int32 i=0;i<Children.Num();i++)
			{
				VerticalBox->AddChildToVerticalBox(Children[i])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);//SetHorizontalAlignment
				if(Children[i] == this)
				{
					VerticalBox->AddChildToVerticalBox(TankOperation->DefaultDragVisual)->SetHorizontalAlignment(HAlign_Center);
				}
			}
		return true;
		}
	}
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if(InOperation && InOperation->DefaultDragVisual)
	{
		RestoreVisuals(InOperation);
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
