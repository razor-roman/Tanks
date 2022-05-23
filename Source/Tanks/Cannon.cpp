// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "Components/ArrowComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent * sceeneCpm =
	CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn 	point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	tempProjectileAuto=ProjectileAuto;
}

void ACannon::Fire()
{
	if(!ReadyToFire)
	{
		return;
	}
	if(ShotCount<=0) return;
	ShotCount--;
	ReadyToFire = false;
	if(Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire -	projectile");
	}
	if (Type == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire - trace");
	}
	if (Type==ECannonType::FireProjectileAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::MultiShot, 1 / FireRateAuto, true,0);
	}
	UE_LOG(LogTemp, Warning, TEXT("ProjectileCount= %f "), ShotCount);
}

void ACannon::FireSpecial()
{
	if(!ReadyToFire)
	{
		return;
	}
	if(ShotCount<=0) return;
	ShotCount--;
	ReadyToFire = false;
	if(Type == ECannonType::FireSpecial)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire -	special");
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,
	&ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::MultiShot()
{
	GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire - multishot",false);
	tempProjectileAuto--;
	if(tempProjectileAuto==0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
		tempProjectileAuto=ProjectileAuto;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);	
	}
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

