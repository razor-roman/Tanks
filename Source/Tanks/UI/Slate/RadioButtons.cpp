// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

#include "Kismet/KismetMathLibrary.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyRadioButtons.Reset();
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	MyRadioButtons = SNew(SSRadioButtonsList)
	.OnRadioButtonChanged_UObject(this,&URadioButtons::HandleOnRadioChoiceChanged);
	auto index = UKismetMathLibrary::Clamp(Index,0,Buttons-1);
	MyRadioButtons->CurrentIndex=index;
	MyRadioButtons->ButtonCount=Buttons;
	MyRadioButtons->Build();
	return MyRadioButtons.ToSharedRef();
}

void URadioButtons::HandleOnRadioChoiceChanged(int32 NewRadioChoise)
{
	if (OnRadioChoiceChanged.IsBound())
    {
    OnRadioChoiceChanged.Broadcast(NewRadioChoise);
    }
}

