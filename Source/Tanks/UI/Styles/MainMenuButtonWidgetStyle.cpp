// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuButtonWidgetStyle.h"

FMainMenuButtonStyle::FMainMenuButtonStyle()
{
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
}

FMainMenuButtonStyle::~FMainMenuButtonStyle()
{
}

const FName FMainMenuButtonStyle::TypeName(TEXT("FMainMenuButtonStyle"));

const FMainMenuButtonStyle& FMainMenuButtonStyle::GetDefault()
{
	static FMainMenuButtonStyle Default;
	return Default;
}

void FMainMenuButtonStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

