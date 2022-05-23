// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos= pawnPos+dir*1000;
	//DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Green, false, 0.1f, 0, 5);
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

void AMyPlayerController::Fire()
{
	TankPawn->Fire();
}

void AMyPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForwardBackward",this,&AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveLeftRight",this,&AMyPlayerController::MoveLeftRight);
	InputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&AMyPlayerController::Fire);
	InputComponent->BindAction("AlternativeFire",EInputEvent::IE_Pressed,this,&AMyPlayerController::FireSpecial);
	
}
