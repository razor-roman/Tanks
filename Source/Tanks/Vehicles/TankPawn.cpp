// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tanks/Controllers/MyPlayerController.h"

ATankPawn::ATankPawn()
{
	
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->bDoCollisionTest = false;
	Arm->bInheritPitch=false;
	Arm->bInheritRoll=false;
	Arm->bInheritYaw=false;
	Arm->SetupAttachment(Body);
	Arm->TargetArmLength = 3000;
	Arm->SetRelativeRotation(FRotator(-90,0,0));
		
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm);
	
	Turret->SetRelativeLocation(FVector(-80,0,100));
	Camera->SetRelativeRotation(FRotator(0,0,0));
	
	HitCollider->SetBoxExtent(FVector(150,150,50));
	HitCollider->SetRelativeLocation(FVector(0,0,110));

	CannonSetupPoint->SetRelativeLocation(FVector(290,0,60));
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

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TankController) RotateTurretTo(TankController->GetMousePos());
	MovePawn(DeltaTime);
	RotatePawn(DeltaTime);
}

void ATankPawn::FireSpecial()
{	
	Cannon->FireSpecial();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController=Cast<AMyPlayerController>(GetController());
}

void ATankPawn::ChangeWeapon()
{
	/*if(first==true)
	{
		first=false;
		UE_LOG(LogTemp, Warning, TEXT("ChangeWeapon SecondCannon %f"));
		SetupCannon(SecondCannon);
		return;
	}
	if(first==false)
	{
		first=true;
		UE_LOG(LogTemp, Warning, TEXT(" ChangeWeapon FirstCannon %f"));
		SetupCannon(FirstCannon);
		return;
	}	*/
}



