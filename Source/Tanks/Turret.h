// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "CommonClass.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
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
	void BeginPlay() override;
	void Destroyed() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	
};