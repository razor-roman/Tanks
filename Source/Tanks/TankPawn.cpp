// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

ATankPawn::ATankPawn()
{
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->bDoCollisionTest = false;
    Arm->bInheritPitch = false;
    Arm->bInheritYaw = false;
    Arm->bInheritRoll = false;
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm);
	//Arm->SetupAttachment(Body);
	//Arm->TargetArmLength = 1200;
	//Turret->SetRelativeLocation(FVector(-80,0,100));
	//Camera->SetRelativeRotation(FRotator(0,-45,0));
	
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation+forwardVector*MoveSpeed*_targetForwardAxisValue*DeltaTime;
	SetActorLocation(movePosition,true);

	FRotator currentRotation = GetActorRotation();
	FRotator rotatePosition=FRotator(0,currentRotation.Yaw+_targetLeftAxisValue*RotationSpeed*DeltaTime,0);
	SetActorRotation(rotatePosition);
}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveLeft(float AxisValue)
{
	_targetLeftAxisValue = AxisValue;
}
