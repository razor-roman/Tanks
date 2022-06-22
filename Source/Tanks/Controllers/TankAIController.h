// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tanks/Vehicles/CommonClass.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public AAIController
{
protected:
	GENERATED_BODY()
	UPROPERTY()
	ACommonClass* TankPawn;
	UPROPERTY()
	APawn * PlayerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	int32 CurrentPatrolPointIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
	float MovementAccurency;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
    float TargetingRange = 1000;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
    float TargetingSpeed = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
    float Accurency = 10;
	//AI
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	float GetRotationgValue();
    void Targeting();
    void RotateToPlayer();
    bool IsPlayerInRange();
    bool CanFire();
	bool IsPlayerSeen();
    void Fire();

	void Initialize();	
};
