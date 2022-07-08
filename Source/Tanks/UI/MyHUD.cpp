// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

AMyHUD::AMyHUD()
{
	
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if(PC)
		{
			//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC,nullptr,EMouseLockMode::DoNotLock,false);
			//PC->bShowMouseCursor = true;
		}
	}
}

UUserWidget* AMyHUD::UseWidget(EWidgetID widgetID, bool RemovePrevious,int32 ZOrder)
{
	if(CurrentWidgetID == widgetID) return CurrentWidget;
	if(RemovePrevious)
	{
		RemoveCurrentWidgetFromViewport();
	}
	TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClasses.FindRef(widgetID);
	if(WidgetClassToUse.Get())
	{
		CurrentWidgetID= widgetID;
		return  AddWidgetToViewportByClass(WidgetClassToUse,ZOrder);
	}
	return nullptr;
}

void AMyHUD::RemoveCurrentWidgetFromViewport()
{
	if(CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget=nullptr;
		CurrentWidgetID = EWidgetID::None;
	}
}

UUserWidget* AMyHUD::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),WidgetClass);
	if(CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}
	return CurrentWidget;
}
