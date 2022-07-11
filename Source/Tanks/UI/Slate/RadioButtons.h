// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSRadioButtonsList.h"
#include "Components/Widget.h"
#include "RadioButtons.generated.h"

class SSRadioButtonsList;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioChoiceChangedEvent,int32, NewSelectedButton);
/**
 * 
 */
UCLASS()
class TANKS_API URadioButtons : public UWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
    FOnRadioChoiceChangedEvent OnRadioChoiceChanged;	
	//~ Begin UVisual Interface
    virtual void ReleaseSlateResources(bool bReleaseChildren) override;
    //~ End UVisual Interface

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Buttons")
	int32 Buttons = 3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Buttons")
	int32 Index = 2;
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface	
	
private:	
	TSharedPtr<SSRadioButtonsList> MyRadioButtons;
	
	void HandleOnRadioChoiceChanged(int32 NewRadioChoise);
};
