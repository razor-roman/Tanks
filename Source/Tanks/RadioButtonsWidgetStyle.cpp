// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtonsWidgetStyle.h"

FRadioButtonsStyle::FRadioButtonsStyle()
{
	CheckBoxStyle=FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("CheckBox");
	TextStyle=FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
}

FRadioButtonsStyle::~FRadioButtonsStyle()
{
}

const FName FRadioButtonsStyle::TypeName(TEXT("FRadioButtonsStyle"));

const FRadioButtonsStyle& FRadioButtonsStyle::GetDefault()
{
	static FRadioButtonsStyle Default;
	return Default;
}

void FRadioButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	CheckBoxStyle.GetResources(OutBrushes);
	TextStyle.GetResources(OutBrushes);
	// Add any brush resources here so that Slate can correctly atlas and reference them
	
}

