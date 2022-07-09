// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawnThirdPersonController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"


ATankPawnThirdPersonController::ATankPawnThirdPersonController()
{
	
}

void ATankPawnThirdPersonController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ATankPawnThirdPersonController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawnThirdPerson>(GetPawn());
	HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->UseWidget(EWidgetID::TankHUD,true,0);
}

 void  ATankPawnThirdPersonController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}

void ATankPawnThirdPersonController::MoveLeftRight(float AxisValue)
{
	TankPawn->MoveLeft(AxisValue);
}

void ATankPawnThirdPersonController::Turn(float AxisValue)
{
	TankPawn->Turn(AxisValue);
}

void ATankPawnThirdPersonController::LookUp(float AxisValue)
{
	TankPawn->LookUp(AxisValue);
}

void ATankPawnThirdPersonController::Fire()
{
	TankPawn->Fire();
}

void ATankPawnThirdPersonController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPawnThirdPersonController::MainMenu()
{
	
	if(HUD)
	{
		if(HUD->CurrentWidgetID==EWidgetID::MainMenu)
		{			
			HUD->UseWidget(EWidgetID::TankHUD,true,0);
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if(PC)
			{
				UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
				PC->bShowMouseCursor = false;
			}
		}
		else if(HUD->CurrentWidgetID==EWidgetID::Settings)
		{
			HUD->UseWidget(EWidgetID::MainMenu,true,0);
		}
		else
		{
			HUD->UseWidget(EWidgetID::MainMenu,false,0);			
		}
		
	}
	else UE_LOG(LogTemp,Warning,TEXT("NO HUD"));
}


void ATankPawnThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&ATankPawnThirdPersonController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&ATankPawnThirdPersonController::MoveLeftRight);
	InputComponent->BindAxis("Turn",this,&ATankPawnThirdPersonController::Turn);
	InputComponent->BindAxis("LookUp",this,&ATankPawnThirdPersonController::LookUp);
	InputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&ATankPawnThirdPersonController::Fire);
	InputComponent->BindAction("AlternativeFire",EInputEvent::IE_Pressed,this,&ATankPawnThirdPersonController::FireSpecial);
	InputComponent->BindAction("MainMenu",EInputEvent::IE_Pressed,this,&ATankPawnThirdPersonController::MainMenu);
	
}
