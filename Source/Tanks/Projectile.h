// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	USceneComponent * SceeneCpm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* OnDestroyAudioEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* OnDestroyParticleEffect;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Movement|Speed")
	float MoveSpeed = 2000;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Movement|Speed")
	float MoveRate = 0.005f;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Movement|Speed")
	float Damage = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float PushForce = 1000;
	
	FTimerHandle MovementTimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Destroy();
	void Start();
protected:
	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Move();	
};
