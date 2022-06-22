// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawnThirdPerson.h"

#include "Tanks/Controllers/TankPawnThirdPersonController.h"


ATankPawnThirdPerson::ATankPawnThirdPerson()
{
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->bDoCollisionTest = false;
    //Arm->bInheritPitch = false;
    //Arm->bInheritYaw = false;
    //Arm->bInheritRoll = false;
	Arm->SetupAttachment(Turret);
	Arm->TargetArmLength = 1200;
	Arm->SetRelativeRotation(FRotator(-10,0,0));
	
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm);
	Turret->SetRelativeLocation(FVector(-80,0,100));
	Camera->SetRelativeRotation(FRotator(0,0,0));
	Turret->SetAbsolute(false,true,false);
	//Body->SetSimulatePhysics(true);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyVisualAsset(TEXT("StaticMesh'/Game/CSC/Meshes/SM_TANK_Base1.SM_TANK_Base1'"));
	if(BodyVisualAsset.Succeeded())
	{ 
		Body->SetStaticMesh(BodyVisualAsset.Object);
		Body->SetRelativeLocation(FVector(0,0,0));
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretVisualAsset(TEXT("StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun6.SM_CSC_Gun6'"));
	if(TurretVisualAsset.Succeeded())
	{
		Turret->SetStaticMesh(TurretVisualAsset.Object);
		Turret->SetRelativeLocation(FVector(-80,0,100));
	}
	
}

void ATankPawnThirdPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	FVector currentLocation = Body->GetRelativeLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation+forwardVector*MoveSpeed*_targetForwardAxisValue*DeltaTime;
	Body->SetRelativeLocation(movePosition,true);

	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue,_targetLeftAxisValue,InterpolationKey);
	FRotator currentRotation = Body->GetRelativeRotation();
	FRotator rotatePosition=FRotator(0,currentRotation.Yaw+CurrentRightAxisValue*RotationSpeed*DeltaTime,0);
	Body->SetRelativeRotation(rotatePosition);

	FRotator TurretcurrentRotation = Turret->GetRelativeRotation();
	float newTurrentRotationPitch= TurretcurrentRotation.Pitch+_targetLookUp*RotationSpeed*DeltaTime;
	float newTurrentRotationYaw= TurretcurrentRotation.Yaw+_targetTurn*RotationSpeed*DeltaTime;
	newTurrentRotationPitch = FMath::Clamp(newTurrentRotationPitch,TurretAngleMin,TurretAngleMax);
	FRotator TurretrotatePosition=FRotator(newTurrentRotationPitch,newTurrentRotationYaw,0);
	Turret->SetRelativeRotation(TurretrotatePosition);

	if(TankController)
	{
		FVector mousePos = TankController->GetMousePos();
	}
}

void ATankPawnThirdPerson::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawnThirdPerson::MoveLeft(float AxisValue)
{
	_targetLeftAxisValue = AxisValue;
}

void ATankPawnThirdPerson::Turn(float AxisValue)
{
	_targetTurn=AxisValue;
}

void ATankPawnThirdPerson::LookUp(float AxisValue)
{
	_targetLookUp=AxisValue;
}

void ATankPawnThirdPerson::FireSpecial()
{
	Cannon->FireSpecial();
}

