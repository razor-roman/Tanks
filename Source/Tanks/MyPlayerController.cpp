// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "DrawDebugHelpers.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos,mouseDirection);
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos,mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos-pawnPos;
	dir.Normalize();
	MousePos = pawnPos+dir*500;
	DrawDebugLine(GetWorld(),pawnPos,MousePos,FColor::Green,false,0.1f,0,0.5);
	
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

void AMyPlayerController::MouseX(float AxisValue)
{
	TankPawn->MouseX(AxisValue);
	
}

void AMyPlayerController::MouseY(float AxisValue)
{
	TankPawn->MouseY(AxisValue);
}

void AMyPlayerController::Arrows(float AxisValue)
{
	TankPawn->Arrows(AxisValue);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&AMyPlayerController::MoveLeftRight);
	InputComponent->BindAxis("Left",this,&AMyPlayerController::MouseX);
	InputComponent->BindAxis("Arrows",this,&AMyPlayerController::Arrows);
}
