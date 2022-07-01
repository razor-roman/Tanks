// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_EVENT_OneParam(UObjectPool,FGetProjectile,AProjectile*)
	DECLARE_EVENT(UObjectPool,FOnDie)
public:	
	// Sets default values for this component's properties
	UObjectPool();
	UFUNCTION()
	AProjectile* GetProjectile();
	
	UPROPERTY(EditAnywhere,Category="Object Pool")
	TSubclassOf<AProjectile> AProjectileSubClass;

	UPROPERTY(EditAnywhere,Category="Object Pool")
	int PoolSize=20;
	int index=0;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	TArray<AProjectile*> ProjectilePool;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
