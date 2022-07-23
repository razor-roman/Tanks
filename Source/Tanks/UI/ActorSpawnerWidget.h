// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Tanks/Vehicles/CommonClass.h"
#include "ActorSpawnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UActorSpawnerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * DraggedText;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Panel;
	UPROPERTY(meta = (BindWidget))
	UImage* ImagePopUp;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextPopUp;
	
	UPROPERTY(EditAnywhere)
	FText DraggedName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnerClass;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	AActor* SpawnedActor;
	void OnMouseButtonUp();
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
