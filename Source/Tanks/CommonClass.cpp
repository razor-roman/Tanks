// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonClass.h"

#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACommonClass::ACommonClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Turret=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLIDER"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HEALTH"));
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	//OnDestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("OnDestroyAudioEffect"));
	//OnDestroyParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnDestroyParticleEffect"));
	
	RootComponent=Body;
	Body->SetupAttachment(RootComponent);
	Turret->SetupAttachment(Body);
	HitCollider->SetupAttachment(RootComponent);
	CannonSetupPoint->AttachToComponent(Turret,FAttachmentTransformRules::KeepRelativeTransform);
	//OnDestroyAudioEffect->SetupAttachment(Body);
	//OnDestroyParticleEffect->SetupAttachment(Body);
	
	HealthComponent->OnDie.AddUObject(this,&ACommonClass::Die);
	HealthComponent->OnDamaged.AddUObject(this,&ACommonClass::DamageTaked);
	
}

// Called when the game starts or when spawned
void ACommonClass::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon(CannonClass);
}

void ACommonClass::Destroyed()
{
	Super::Destroyed();
}

// Called every frame
void ACommonClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
}

// Called to bind functionality to input
void ACommonClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACommonClass::Die()
{
	if(Cannon)
		Cannon->Destroy();
	//OnDestroyParticleEffect->ActivateSystem();
	//OnDestroyAudioEffect->Play();
	//SetLifeSpan(5);
	Destroy();
}

void ACommonClass::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(),
DamageValue, HealthComponent->GetHealth());
}

void ACommonClass::TakeDamage(FDamageData DamageData)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f "), *GetName(),DamageData.DamageValue);
	HealthComponent->TakeDamage(DamageData);
}

void ACommonClass::ScoreUp(float Score)
{
	ScoreNumber+=Score;
}

void ACommonClass::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ACommonClass::MoveLeft(float AxisValue)
{
	_targetLeftAxisValue = AxisValue;
}

void ACommonClass::MovePawn(float DeltaTime)
{
	FVector currentLocation = Body->GetRelativeLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation+forwardVector*MoveSpeed*_targetForwardAxisValue*DeltaTime;
	Body->SetRelativeLocation(movePosition,true);
}

void ACommonClass::RotatePawn(float DeltaTime)
{
	//interpolatedYaw = FMath::Lerp(interpolatedYaw,_targetLeftAxisValue,InterpolationKey);
	float yawRotation = RotationSpeed * _targetLeftAxisValue * DeltaTime;
	FRotator bodyCurrentRotation = Body->GetRelativeRotation();	
	float bodyRotation = bodyCurrentRotation.Yaw+yawRotation;	
	Body->SetRelativeRotation(FRotator(0,bodyRotation,0));	
}

void ACommonClass::Fire()
{
	Cannon->Fire();
}

void ACommonClass::SetupCannon(TSubclassOf<ACannon> cannon)
{
	/*if(FirstCannon==NULL)
	{		
		FirstCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("FirstCannon %f"),SecondCannon.GetDefaultObject());
	}
	else if(cannon!=FirstCannon)
	{		
		SecondCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("SecondCannon %f"),FirstCannon.GetDefaultObject());
	}*/
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

void ACommonClass::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(Turret->GetComponentLocation(), TargetPosition);
	FRotator currRotation = Turret->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	Turret->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));

}

FVector ACommonClass::GetTurretForwardVector()
{
	return  Turret->GetForwardVector();
}

FVector ACommonClass::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}


