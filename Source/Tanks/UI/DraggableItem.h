// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DraggableItem.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * TankText;

	UPROPERTY(EditAnywhere)
    FText TankName;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	UFUNCTION()
	void RestoreVisuals(UDragDropOperation* Operation);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	
};
