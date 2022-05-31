// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "CommonClass.h"
#include "TankPawn.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATurret : public ACommonClass
{
	
	GENERATED_BODY()
	ATurret();
protected:
	UPROPERTY(EditAnywhere)
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitCollider;

	UPROPERTY()
	ACannon* Cannon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingRange=1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingSpeed=0.1f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingRate=0.005f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float Accurency=10;
protected:
	void BeginPlay() override;
	void Destroyed() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	
	
};
