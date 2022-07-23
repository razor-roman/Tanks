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
	PC = GetWorld()->GetFirstPlayerController();
	
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
	if(HUD && PC)
	{
		if(HUD->CurrentWidgetID==EWidgetID::MainMenu)
		{			
			HUD->UseWidget(EWidgetID::TankHUD,true,0);
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
			PC->bShowMouseCursor = false;
		}
		else if(HUD->CurrentWidgetID==EWidgetID::Settings)
		{
			HUD->UseWidget(EWidgetID::MainMenu,true,0);
		}
		else
		{
			HUD->UseWidget(EWidgetID::MainMenu,true,0);			
		}
		
	}
	else UE_LOG(LogTemp,Warning,TEXT("NO HUD"));
}

void ATankPawnThirdPersonController::Inventory()
{
	InventoryManagerComponent = TankPawn->InventoryManagerComponent; // TODO class CAST
	if(!InventoryManagerComponent) UE_LOG(LogActor,Warning,TEXT("!InventoryManagerComponent"));	
	InventoryComponent = TankPawn->InventoryComponent; // TODO class CAST
	if(!InventoryComponent) UE_LOG(LogActor,Warning,TEXT("!InventoryComponent"));
	InventoryManagerComponent->Init(InventoryComponent);
	if(HUD && PC)
	{
		if(HUD->CurrentWidgetID==EWidgetID::Inventory)
		{			
			HUD->UseWidget(EWidgetID::TankHUD,true,0);			
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
			PC->bShowMouseCursor = false;			
		}
		else
		{
			HUD->UseWidget(EWidgetID::Inventory,true,0);
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
			PC->bShowMouseCursor = true;
		}
	}
	else UE_LOG(LogTemp,Warning,TEXT("NO HUD"));
}

void ATankPawnThirdPersonController::DragAndDrop()
{
	SetWidget(EWidgetID::DragDrop,true,0);
}

void ATankPawnThirdPersonController::SetWidget(EWidgetID Widget, bool bRemotePrevious, int ZOrder)
{	
	if(HUD && PC)
	{
		if(HUD->CurrentWidgetID==Widget)
		{
			HUD->UseWidget(EWidgetID::TankHUD,bRemotePrevious,ZOrder);			
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
			PC->bShowMouseCursor = false;	
		}
		else
		{
			HUD->UseWidget(Widget,bRemotePrevious,ZOrder);
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
			PC->bShowMouseCursor = true;
		}
	}
}


void ATankPawnThirdPersonController::OnLeftMouseButtonUp()
{
	if(OnMouseButtonUp.IsBound())
	{
		OnMouseButtonUp.Broadcast();
	}
	
}

void ATankPawnThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&ThisClass::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&ThisClass::MoveLeftRight);
	InputComponent->BindAxis("Turn",this,&ThisClass::Turn);
	InputComponent->BindAxis("LookUp",this,&ThisClass::LookUp);
	InputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&ThisClass::Fire);
	InputComponent->BindAction("AlternativeFire",EInputEvent::IE_Pressed,this,&ThisClass::FireSpecial);
	InputComponent->BindAction("MainMenu",EInputEvent::IE_Pressed,this,&ThisClass::MainMenu);
	InputComponent->BindAction("Inventory",EInputEvent::IE_Pressed,this,&ThisClass::Inventory);
	InputComponent->BindAction("DragAndDrop",EInputEvent::IE_Pressed,this,&ThisClass::DragAndDrop);
	InputComponent->BindKey(EKeys::LeftMouseButton,IE_Released,this,&ThisClass::OnLeftMouseButtonUp);
}
