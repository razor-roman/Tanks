// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PooledObject.h"
#include "ObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();
	
	UFUNCTION(BlueprintCallable,Category="Object Pool")
	APooledObject* SpawnPooledObject();

	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);
	
	UPROPERTY(EditAnywhere,Category="Object Pool")
	TSubclassOf<class APooledObject> PooledObjectSubClass;
	
	UPROPERTY(EditAnywhere,Category="Object Pool")
	int PoolSize = 20;
	
	UPROPERTY(EditAnywhere,Category="Object Pool")
	float PooledObjectLifeSpan = 0.0f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<APooledObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;
};
