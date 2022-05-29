// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include <Actor.h>

#include "DrawDebugHelpers.h"
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
	ProjectileSpawnPoint->SetupAttachment(Mesh);

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
	if(ProjectileCount<=0 && TraceCount<=0) return;
	
	ReadyToFire = false;
	if(Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire -	projectile");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			Mesh->GetComponentLocation(),
			Mesh->GetComponentRotation());
		if(projectile)
		{
			projectile->Start();
		}
		else
		{
			UE_LOG(LogTemp,Verbose,TEXT("NO PROJECTILE"));
		}
		ProjectileCount--;
	}
	if (Type == ECannonType::FireTrace)
	{
		FHitResult HitResult;
		FCollisionQueryParams traceParams=FCollisionQueryParams(FName(TEXT("FireTrace")),
			true,this);
		traceParams.bTraceComplex=true;
		traceParams.bReturnPhysicalMaterial = false;
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector()*FireRange+start;
		if(GetWorld()->LineTraceSingleByChannel(HitResult, start, end,
        ECollisionChannel::ECC_Visibility, traceParams))
	        {
		        DrawDebugLine(GetWorld(), start, HitResult.Location, FColor::Red, false,
		        0.5f, 0, 5);
		        if(HitResult.Actor.Get())
			        {
			        HitResult.Actor.Get()->Destroy();
			        }
	        }
        else
	        {
	        DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
	        }
		TraceCount--;
	}
	if (Type==ECannonType::FireProjectileAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::MultiShot, 1 / FireRateAuto, true,0);
		ProjectileCount--;
	}
	UE_LOG(LogTemp, Warning, TEXT("ProjectileCount= %f, TraceCount= %f "), ProjectileCount,TraceCount);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if(!ReadyToFire)
	{
		return;
	}
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

void ACannon::AddProjectile(float count)
{
	ProjectileCount+=count;
}

void ACannon::AddTrace(float count)
{
	TraceCount+=count;
}


// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

