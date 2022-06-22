// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
};