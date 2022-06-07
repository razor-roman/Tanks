// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATankFactory::ATankFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building 	Mesh"));
	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	OnDestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("OnDestroyAudioEffect"));
	OnSpawnTankAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("OnSpawnTankAudioEffect"));
	OnDestroyParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnDestroyParticleEffect"));
	
	RootComponent = sceneComp;
	BuildingMesh->SetupAttachment(sceneComp);
	TankSpawnPoint->AttachToComponent(sceneComp,FAttachmentTransformRules::KeepRelativeTransform);
	HitCollider->SetupAttachment(sceneComp);
	OnDestroyAudioEffect->SetupAttachment(BuildingMesh);
	OnSpawnTankAudioEffect->SetupAttachment(BuildingMesh);
	OnDestroyParticleEffect->SetupAttachment(BuildingMesh);
	
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::DamageTaked);
	
	OnSpawnTankAudioEffect->SetAutoActivate(false);
	OnDestroyAudioEffect->SetAutoActivate(false);
	OnDestroyParticleEffect->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ATankFactory::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,&ATankFactory::SpawnNewTank, SpawnTankRate, false, SpawnTankRate);
	HealthComponent->SetHealth(Health);
	
}

// Called every frame
void ATankFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankFactory::SpawnNewTank()
{
	OnSpawnTankAudioEffect->Play();
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(),TankSpawnPoint->GetComponentLocation(),FVector(1));

	ACommonClass * newTank = GetWorld()->SpawnActorDeferred<ACommonClass>(SpawnTankClass, 
		spawnTransform,this,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	newTank->SetTargetPoints(TankWayPoints);	
	UGameplayStatics::FinishSpawningActor(newTank,spawnTransform);
}

void ATankFactory::Die()
{
	if(LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);
	UStaticMesh * bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if(bodyMeshTemp)
	{
		BuildingMesh->SetStaticMesh(bodyMeshTemp);
		BuildingMesh->SetWorldScale3D(FVector(5,5,5));
	}
	OnDestroyParticleEffect->ActivateSystem();
	OnDestroyAudioEffect->Play();
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"),*GetName(), DamageValue, HealthComponent->GetHealth());
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

