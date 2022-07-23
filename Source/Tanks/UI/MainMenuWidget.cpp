// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "MyHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Styles/StyleSet.h"

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
	if(OptionBtn)
	{
		OptionBtn->OnClicked.RemoveAll(this);
	}
}

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	 if (NewGameBtn)
	 {
	 	NewGameBtn->WidgetStyle = FStyleSet::Get ().GetWidgetStyle<FButtonStyle>(ButtonStyleSet);
	 }
	if (QuitBtn)
	{
		QuitBtn->WidgetStyle = FStyleSet::Get ().GetWidgetStyle<FButtonStyle>(ButtonStyleSet);
	}
	if (OptionBtn)
	{
		OptionBtn->WidgetStyle = FStyleSet::Get ().GetWidgetStyle<FButtonStyle>(ButtonStyleSet);
	}
	if (LoadBtn)
	{
		LoadBtn->WidgetStyle = FStyleSet::Get ().GetWidgetStyle<FButtonStyle>(ButtonStyleSet);
	}
	if(LevelSelectButton)
	{
		LevelSelectButton->WidgetStyle = FStyleSet::Get().GetWidgetStyle<FRadioButtonsStyle>(RadioButtonStyleSet);		
	}
}

void UMainMenuWidget::OnNewGameClicked()
{	
	UGameplayStatics::OpenLevel(GetWorld(),"NewMap");  
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		PC->bShowMouseCursor = false;
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
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
