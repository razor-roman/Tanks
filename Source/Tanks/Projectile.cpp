// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "ComponentUtils.h"
#include "DamageTaker.h"
#include "IScorable.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent=SceeneCpm;
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
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
	
	UE_LOG(LogTemp,Warning,TEXT("Projectile %s collide with %s."),*GetName(),*OtherActor->GetName());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr? owner->GetOwner() : nullptr;
	
	if(OtherActor!= owner && OtherActor!=ownerByOwner)
	{
		IDamageTaker * damageTakerActor = Cast<IDamageTaker>(OtherActor);
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
			OtherActor->Destroy();
		}
		Destroy();
	}
}

