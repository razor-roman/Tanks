// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Slate/RadioButtons.h"
#include "MainMenuWidget.generated.h"

class AMyHUD;
/**
 * 
 */
UCLASS(Abstract)
class TANKS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual  void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativePreConstruct() override;
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* NewGameBtn;
	UPROPERTY(meta=(BindWidget))
	UButton* LoadBtn;
	UPROPERTY(meta=(BindWidget))
	UButton* OptionBtn;
	UPROPERTY(meta=(BindWidget))
	UButton* QuitBtn;
	UPROPERTY(meta=(BindWidget))
	URadioButtons* LevelSelectButton;
	UPROPERTY(meta=(BindWidgetAnim),Transient)
	UWidgetAnimation* TestAnimation;
	UPROPERTY(EditAnywhere, Category = "Style");
	FName ButtonStyleSet;
	UPROPERTY(EditAnywhere, Category = "Style");
	FName RadioButtonStyleSet;
	UPROPERTY()
	AMyHUD* HUD;
	UFUNCTION()
	void OnNewGameClicked();
	UFUNCTION()
	void OnQuitClicked();
	UFUNCTION()
	void OnOptionClicked();
};
