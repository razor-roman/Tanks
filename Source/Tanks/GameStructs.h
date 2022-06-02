// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
	FireSpecial = 2 UMETA(DisplayName = "Use special"),
	FireProjectileAuto = 3 UMETA(DisplayName = "Use projectile auto")
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()
	UPROPERTY()
	float DamageValue;
	UPROPERTY()
	AActor* Instigator;
	UPROPERTY()
	AActor* DamageMaker;
};

USTRUCT()
struct FScoreData
{
	GENERATED_BODY()
	UPROPERTY()
	float Turret=50;
	float Tank=100;
};
