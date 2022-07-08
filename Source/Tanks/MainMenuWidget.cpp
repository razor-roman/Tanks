// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/MyHUD.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(NewGameBtn)
	{
		NewGameBtn->OnClicked.AddDynamic(this,&UMainMenuWidget::OnNewGameClicked);
	}
	if(QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this,&UMainMenuWidget::OnQuitClicked);
	}
	if(OptionBtn)
	{
		OptionBtn->OnClicked.AddDynamic(this,&UMainMenuWidget::OnOptionClicked);
	}
	PlayAnimation(TestAnimation);
	HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if(PC)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC,nullptr,EMouseLockMode::LockAlways,false);
			PC->bShowMouseCursor = true;
		}
	}
}

void UMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if(NewGameBtn)
	{
		NewGameBtn->OnClicked.RemoveAll(this);
	}
	if(QuitBtn)
	{
		QuitBtn->OnClicked.RemoveAll(this);
	}
}

void UMainMenuWidget::OnNewGameClicked()
{
	if(TestAnimation)
	{
		PlayAnimation(TestAnimation);
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	//GEngine->Exec(GetWorld(),TEXT("Quit"));
}

void UMainMenuWidget::OnOptionClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("OnOptionClicked"));
	if(HUD)
	{
		HUD->UseWidget(EWidgetID::Settings,true,0);
	}
	else UE_LOG(LogTemp,Warning,TEXT("NO HUD"));
}
