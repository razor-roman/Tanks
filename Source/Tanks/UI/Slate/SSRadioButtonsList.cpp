// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRadioButtonsList.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSRadioButtonsList::Construct(const FArguments& InArgs)
{
	OnRadioChoiceChanged = InArgs._OnRadioButtonChanged;
	ChildSlot
	[
		SAssignNew(RadioBox,SVerticalBox)
	];
	if(RadioBox->NumSlots()!=ButtonCount)
	{
		Build();
	}	
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
		[
			SNew(STextBlock)
			.Text(FText::FromString(InText)) 
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION



