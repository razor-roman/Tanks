// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"

#include <complex>

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AProjectile* UObjectPool::GetProjectile()
{
	if(index>=PoolSize-1)
	{
		index=0;
	}
	else
	{
		++index;
	}
	AProjectile* projectile = ProjectilePool[index];
	UE_LOG(LogTemp,Warning,TEXT("index= %f"),(float)index);
	return projectile;
}


/*AProjectile* UObjectPool::SpawnProjectileObject()
{
	for (AProjectile* Projectile : ProjectilePool)
	{
		if(Projectile!=nullptr) 
		{
			Projectile->TeleportTo(FVector().ZeroVector,FRotator().ZeroRotator);
		}
		return Projectile; 
	}
	return nullptr;
}*/


// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if(AProjectileSubClass!=nullptr)
	{
		UWorld* const World = GetWorld();
		if(World!=nullptr)
		{
			for (int i=0;i<PoolSize;i++)
			{
				AProjectile* Projectile = World->SpawnActor<AProjectile>(AProjectileSubClass,
					FVector().ZeroVector,FRotator().ZeroRotator);
				if(Projectile!=nullptr)
				{
					Projectile->Stop();
					ProjectilePool.Add(Projectile);
				}
			}
		}
	}
	// ...
	
}


// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

