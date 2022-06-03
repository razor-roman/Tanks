// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "IScorable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "CommonClass.generated.h"

UCLASS()
class TANKS_API ACommonClass : public APawn, public IDamageTaker, public IIScorable 
{
	GENERATED_BODY()

protected:
	// Sets default values for this pawn's properties
	ACommonClass();
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Turret;
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitCollider;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent * CannonSetupPoint;
	float Health=1;
	UPROPERTY()
	float ScoreNumber=0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACannon> CannonClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY()
	ACannon* Cannon;
	UPROPERTY()
	APawn* PlayerPawn;
	
	UFUNCTION()
	void Die();
	UFUNCTION()
	void DamageTaked(float DamageValue);
public:
	virtual void TakeDamage(FDamageData DamageData) override;
	virtual void ScoreUp(float Score) override;
	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);
	void Fire();
	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);
protected:
	float _targetForwardAxisValue;
	float _targetLeftAxisValue;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float InterpolationKey = 0.03f;
	float TurretRotationInterpolationKey=0.1f;
//AI
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
	float MovementAccurency = 50;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingRange=1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingSpeed=0.1f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float TargetingRate=0.005f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Targeting")
	float Accurency=10;
public:
	UFUNCTION()
	float GetMovementAccurency()
	{
		return MovementAccurency;
	};
	UFUNCTION()
	TArray<FVector> GetPatrollingPoints()
	{
		return PatrollingPoints;
	};
	UFUNCTION()
	FVector GetTurretForwardVector();
	FVector GetEyesPosition();
};
