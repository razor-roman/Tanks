// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ActorComponents/PhysicsComponent.h"
#include "PhysicsProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API APhysicsProjectile : public AProjectile
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPhysicsComponent* PhysicsComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent * TrailEffect;

	UPROPERTY()
	APawn * PlayerPawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveAccurency = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationMaxTime = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationTimeStep = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationSpeed = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Trajectory")
	bool ShowTrajectory = false;

	UPROPERTY(EditAnywhere, Category = "Movement params")
	FVector MoveVector;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement params")
	TArray<FVector> CurrentTrajectory;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement params")
	int32 TragectoryPointIndex;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Explode")
	float ExplodeRadius=50;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Explode")
	bool bExplode=false;
public:
	APhysicsProjectile();
	virtual void Start(FVector StartPos,FRotator ForwardVector) override;
protected:
	virtual void Move() override;
	void Explode();
};
