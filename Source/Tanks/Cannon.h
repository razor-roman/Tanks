// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "ObjectPool.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class UArrowComponent;
UCLASS()
class TANKS_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent * ProjectileSpawnPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* ShootEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UForceFeedbackEffect * ShootForceEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pool")	
	UObjectPool* Pool;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> ShootShake;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRateAuto = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireDamage = 1;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Movement|Speed")
	float TraceDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;
	FTimerHandle ReloadTimerHandle;
	bool ReadyToFire = false;
public:
	UPROPERTY(EditAnywhere)
	float ProjectileCount=10;
	UPROPERTY(EditAnywhere)
	float TraceCount=10;
protected:
	UPROPERTY(EditAnywhere)
	float ProjectileAuto=3;
	float tempProjectileAuto;
	
public:
	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
	void MultiShot();
	void AddProjectile(float count);
	void AddTrace(float count);
	/*ACannon operator+ (ACannon const lhs, ACannon const rhs) {
		ACannon Tmp;
		Tmp.ProjectileCount += rhs.ProjectileCount;
		return Tmp;
	}*/
protected:
	void Reload();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Fire params")
	TSubclassOf<AProjectile> ProjectileClass;
	

};
