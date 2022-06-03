// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "MyPlayerController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	
	FVector currentLocation = Body->GetRelativeLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation+forwardVector*MoveSpeed*_targetForwardAxisValue*DeltaTime;
	Body->SetRelativeLocation(movePosition,true);

	//interpolatedYaw = FMath::Lerp(interpolatedYaw,_targetLeftAxisValue,InterpolationKey);
	float yawRotation = RotationSpeed * _targetLeftAxisValue * DeltaTime;
	FRotator bodyCurrentRotation = Body->GetRelativeRotation();	
	float bodyRotation = bodyCurrentRotation.Yaw+yawRotation;	
	Body->SetRelativeRotation(FRotator(0,bodyRotation,0));
	if(TankController)
	{
		RotateTurretTo(TankController->GetMousePos());			
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO CONTROLLER"));
	}
	
	
}

void ATankPawn::FireSpecial()
{	
	Cannon->FireSpecial();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController=Cast<AMyPlayerController>(GetController());
	SetupCannon(FirstCannon);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> cannon)
{	
	if(FirstCannon==NULL)
	{		
		FirstCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("FirstCannon %f"),SecondCannon.GetDefaultObject());
	}
	else if(cannon!=FirstCannon)
	{		
		SecondCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("SecondCannon %f"),FirstCannon.GetDefaultObject());
	}
	if(Cannon)
	{
		Cannon->Destroy();		
	}	
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(cannon, params);	
	Cannon->AttachToComponent(CannonSetupPoint,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATankPawn::ChangeWeapon()
{
	if(first==true)
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
	}
	
}


