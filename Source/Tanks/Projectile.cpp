// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "ComponentUtils.h"
#include "DamageTaker.h"
#include "IScorable.h"
#include "TankPawn.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	OnDestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("OnDestroyAudioEffect"));
	OnDestroyParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnDestroyParticleEffect"));
	
	RootComponent=SceeneCpm;
	Mesh->SetupAttachment(RootComponent);
	OnDestroyAudioEffect->SetupAttachment(RootComponent);
	OnDestroyParticleEffect->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	
	OnDestroyAudioEffect->SetAutoActivate(false);
	OnDestroyParticleEffect->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Destroy()
{
	OnDestroyParticleEffect->ActivateSystem();
	OnDestroyAudioEffect->Play();
	MoveSpeed=0;
	Mesh->SetHiddenInGame(true);
	SetLifeSpan(0.5);
}


void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed
* MoveRate;
	SetActorLocation(nextPosition);
	
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle,this,
		&AProjectile::Move,MoveRate,true,MoveRate);
	
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
                                     OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
                                     bFromSweep, const FHitResult& SweepResult)
{	
	//UE_LOG(LogTemp,Warning,TEXT("Projectile %s collide with %s."),*GetName(),*OtherActor->GetName());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr? owner->GetOwner() : nullptr;
	
	if(OtherActor!= owner && OtherActor!=ownerByOwner)
	{
		IDamageTaker * damageTakerActor = Cast<IDamageTaker>(OtherActor);
		ATankPawn * playerPawn = Cast<ATankPawn>(OtherActor);
		if(damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;
			damageTakerActor->TakeDamage(damageData);
		}
		else
		{
			UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if(mesh)
			{
				if(mesh->IsSimulatingPhysics())
				{
					FVector forceVector=OtherActor->GetActorLocation() - GetActorLocation();
					forceVector.Normalize();
					mesh->AddImpulse(forceVector*PushForce,NAME_None,true);
				}
			}
		}
		AProjectile::Destroy();
	}
	AProjectile::Destroy();
}

