// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "DrawDebugHelpers.h"


AMyPlayerController::AMyPlayerController()
{
	
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
	
}

 void  AMyPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}

void AMyPlayerController::MoveLeftRight(float AxisValue)
{
	TankPawn->MoveLeft(AxisValue);
}

void AMyPlayerController::Turn(float AxisValue)
{
	TankPawn->Turn(AxisValue);
}

void AMyPlayerController::LookUp(float AxisValue)
{
	TankPawn->LookUp(AxisValue);
}



void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&AMyPlayerController::MoveLeftRight);
	InputComponent->BindAxis("Turn",this,&AMyPlayerController::Turn);
	InputComponent->BindAxis("LookUp",this,&AMyPlayerController::LookUp);
	
}
