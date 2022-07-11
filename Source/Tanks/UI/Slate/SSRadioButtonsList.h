// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)
	
	SLATE_END_ARGS()	
	
	void Construct(const FArguments& InArgs);

	int32 ButtonCount;

	int32 CurrentIndex;

	void Build();
protected:
	
	FOnRadioButtonChanged OnRadioChoiceChanged;
	
	TSharedRef<SWidget> CreateCheckBox(int32 InIndex,FString InText);
	
	ECheckBoxState IsChecked(int32 InIndex) const;
	
	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex);
	
	TSharedPtr<SVerticalBox> RadioBox;
	
};
