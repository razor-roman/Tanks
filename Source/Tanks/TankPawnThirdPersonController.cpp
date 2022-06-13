// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawnThirdPersonController.h"


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


void ATankPawnThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&ATankPawnThirdPersonController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&ATankPawnThirdPersonController::MoveLeftRight);
	InputComponent->BindAxis("Turn",this,&ATankPawnThirdPersonController::Turn);
	InputComponent->BindAxis("LookUp",this,&ATankPawnThirdPersonController::LookUp);
	InputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&ATankPawnThirdPersonController::Fire);
	InputComponent->BindAction("AlternativeFire",EInputEvent::IE_Pressed,this,&ATankPawnThirdPersonController::FireSpecial);
	
}
