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
	//UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController %f") );
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


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&AMyPlayerController::MoveLeftRight);
}
