// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"
UENUM()
enum class EWidgetID : uint8
{	
	None,
	MainMenu,
	PauseMenu,
	Settings,
	TankHUD,
	GameOver,
	Inventory,
};
/**
 * 
 */
UCLASS(Abstract)
class TANKS_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMyHUD();
protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION(BlueprintCallable)
	UUserWidget* UseWidget(EWidgetID widgetID, bool RemovePrevious,int32 ZOrder);

	UPROPERTY(EditAnywhere)
	TMap<EWidgetID,TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	EWidgetID CurrentWidgetID;

	UFUNCTION(BlueprintCallable)
	void RemoveCurrentWidgetFromViewport();

	UUserWidget * AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);
};
