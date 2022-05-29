// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	
}

void APooledObject::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

void APooledObject::SetActive(bool IsActive)
{
	Active=IsActive;
	SetActorHiddenInGame(!Active);
	GetWorldTimerManager().SetTimer(LifeSpanTimer,this,&APooledObject::Deactivate,LifeSpan,false);
}

void APooledObject::SetLifeSpan(float LifeTime)
{
	LifeSpan=LifeTime;
}

void APooledObject::SetPoolIndex(int Index)
{
	PoolIndex=Index;
}

bool APooledObject::IsActive()
{
	return Active;
}

int APooledObject::GetPoolIndex()
{
	return PoolIndex;
}

// Called when the game starts or when spawned
void APooledObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APooledObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

