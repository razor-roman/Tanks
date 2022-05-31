// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/KismetMathLibrary.h"

ATurret::ATurret()
{
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SETUP_POINT"));
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLIDER"));
	CannonSetupPoint->SetupAttachment(Turret);
	HitCollider->SetupAttachment(RootComponent);
	
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters params;
	params.Owner=this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass,params);
	Cannon->AttachToComponent(CannonSetupPoint,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle,this,&ATurret::Targeting,TargetingRate,true,TargetingRate);
	
}

void ATurret::Destroyed()
{
	Super::Destroyed();
	if(Cannon)
		Cannon->Destroy();
}

void ATurret::Targeting()
{
	if(IsPlayerInRange())
	{
		RotateToPlayer();
	}
	if(CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),PlayerPawn->GetActorLocation());
	FRotator currRotation = Turret->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	Turret->SetWorldRotation(FMath::Lerp(currRotation,targetRotation,TargetingSpeed));

}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = Turret->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle =  FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir,dirToPlayer)));
	return aimAngle <= Accurency;
}

void ATurret::Fire()
{
	if(Cannon)
		Cannon->Fire();
}
