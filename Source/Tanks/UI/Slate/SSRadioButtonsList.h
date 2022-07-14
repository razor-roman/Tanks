// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tanks/UI/Styles/RadioButtonsWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewRadioChoise*/);
/**
 * 
 */
class TANKS_API SSRadioButtonsList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSRadioButtonsList)
	{
		
	}
	/** The visual style of the radio button */
	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)
	
	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)
	
	SLATE_END_ARGS()
	
	/** See ButtonStyle attribute */
	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);
	void Construct(const FArguments& InArgs);

	int32 ButtonCount;

	int32 CurrentIndex;

	void Build();
protected:
	
	/** Style resource for check boxes */
	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	/** Style resource for text */
	const FTextBlockStyle* TextStyle = nullptr;
	
	FOnRadioButtonChanged OnRadioChoiceChanged;
	
	TSharedRef<SWidget> CreateCheckBox(int32 InIndex,FString InText);
	
	ECheckBoxState IsChecked(int32 InIndex) const;
	
	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex);
	
	TSharedPtr<SVerticalBox> RadioBox;
	
};
