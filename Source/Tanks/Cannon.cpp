// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "DrawDebugHelpers.h"
#include "ObjectPool.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Interfaces/DamageTaker.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent * sceeneCpm =
	CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn 	point"));
	Pool = CreateDefaultSubobject<UObjectPool>(TEXT("Pool"));

	RootComponent = sceeneCpm;
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint->SetupAttachment(Mesh);	
	AudioEffect->SetupAttachment(Mesh);
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);
	
	ProjectileSpawnPoint->SetRelativeLocation(FVector(290,0,50));
	
	ShootEffect->SetAutoActivate(false);
	AudioEffect->SetAutoActivate(false);
	
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
	ShootEffect->ActivateSystem();
    AudioEffect->Play();
	if(GetOwner()&&GetOwner()==GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		if(ShootForceEffect)
		{
			FForceFeedbackParameters shootForceEffectParams;
			shootForceEffectParams.bLooping = false;
			shootForceEffectParams.Tag = "shootForceEffectParams";
		GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ShootForceEffect,shootForceEffectParams);
		}
		if(ShootShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ShootShake);
		}
	}
	if(Type == ECannonType::FireProjectile)
	{
		auto projectile = Pool->GetProjectile();
		/*GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire -	projectile");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			Mesh->GetComponentLocation(),
			Mesh->GetComponentRotation());*/
		if(projectile)
		{			
			projectile->Start(ProjectileSpawnPoint->GetComponentLocation(),
				ProjectileSpawnPoint->GetComponentRotation());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("NO PROJECTILE"));
		}
		ProjectileCount--;
	}
	if(Type == ECannonType::FireTrace)
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
			AActor* OtherActor = HitResult.Actor.Get();
			UE_LOG(LogTemp,Warning,TEXT("Trace %s collide with %s."),*GetName(),*OtherActor->GetName());
			AActor* owner = GetOwner();
			AActor* ownerByOwner = owner != nullptr? owner->GetOwner() : nullptr;
			if(OtherActor!= owner && OtherActor!=ownerByOwner)
			{
				IDamageTaker * damageTakerActor = Cast<IDamageTaker>(OtherActor);
				if(damageTakerActor)
				{
					FDamageData damageData;
					damageData.DamageValue = TraceDamage;
					damageData.Instigator = owner;
					damageData.DamageMaker = this;
					damageTakerActor->TakeDamage(damageData);
				}
				else
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

