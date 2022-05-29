// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	// ...
}


APooledObject* UObjectPool::SpawnPooledObject()
{
	for (APooledObject* PoolableActor : ObjectPool)
	{
		if(PoolableActor!=nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector(0,0,0),FRotator(0,0,0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}
	if(SpawnedPoolIndexes.Num()>0) //???
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		APooledObject* PoolableActor = ObjectPool[PooledObjectIndex];
		
		if(PoolableActor!= nullptr)
		{
			PoolableActor->SetActive(false);
			
			PoolableActor->TeleportTo(FVector(0,0,0),FRotator(0,0,0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
		}
	}
	return nullptr;
}

void UObjectPool::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if(PooledObjectSubClass!=nullptr)
	{
		UWorld* const World = GetWorld();
		if(World!=nullptr)
		{
			for (int i=0; i< PoolSize;i++)
			{
				APooledObject* PoolableActor = World->SpawnActor<APooledObject>(PooledObjectSubClass,FVector().ZeroVector,FRotator().ZeroRotator);
				if(PoolableActor!=nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this,&UObjectPool::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);					
				}
			}
		}
	}
	// ...
	
}


