// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRadioButtonsList.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SSRadioButtonsList::Construct(const FArguments& InArgs)
{
	OnRadioChoiceChanged = InArgs._OnRadioButtonChanged;
	SetRadioButtonStyle(InArgs._Style);
	ChildSlot
	[
		SAssignNew(RadioBox,SVerticalBox)
	];
	if(RadioBox->NumSlots()!=ButtonCount)
	{
		Build();
	}	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSRadioButtonsList::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextStyle = &InStyle->TextStyle;
}

void SSRadioButtonsList::Build()
{
	RadioBox->ClearChildren();
	for (int i=0;i<ButtonCount;i++)
	{
		RadioBox->AddSlot()
		[
			CreateCheckBox(i,TEXT("Option ") + FString::FromInt(i))
		];
	}
	OnRadioChoiceChanged.ExecuteIfBound(CurrentIndex);
}



TSharedRef<SWidget> SSRadioButtonsList::CreateCheckBox(int32 InIndex, FString InText)
{
	return SNew(SCheckBox)
	.IsChecked_Raw(this, &SSRadioButtonsList::IsChecked,InIndex)
	.OnCheckStateChanged(this, &SSRadioButtonsList::OnCheckBoxStateChanged,InIndex)
	.Style(CheckBoxStyle)
		[
			SNew(STextBlock)
			.Text(FText::FromString(InText))
			.TextStyle(TextStyle)
		];
}


ECheckBoxState SSRadioButtonsList::IsChecked(int32 InIndex) const
{
	return (CurrentIndex == InIndex) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSRadioButtonsList::OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		OnRadioChoiceChanged.ExecuteIfBound(CurrentIndex);
	}
}




