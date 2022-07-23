// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Pawn.h"
#include "Tanks/Cannon.h"
#include "Tanks/ActorComponents/HealthComponent.h"
#include "Tanks/Interfaces/DamageTaker.h"
#include "Tanks/Interfaces/IScorable.h"
#include "Tanks/UI/HealthBar.h"
#include "CommonClass.generated.h"

class UWidgetInteractionComponent;
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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* OnDestroyAudioEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* OnDestroyParticleEffect;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UWidgetComponent* WidgetComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UHealthBar> HealthWidget;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	// UWidgetInteractionComponent* WidgetInteract;
	UPROPERTY(EditAnywhere,Category="Health");
	float Health=1;
	UPROPERTY()
	float ScoreNumber=0;
	FVector PlayerStart;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Variables")
	bool bIsDead;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACannon> CannonClass;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* PopUpPic;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY()
	UHealthBar* HealthBar;
	UPROPERTY()
	ACannon* Cannon;
	
	UFUNCTION()
	void Die();
	UFUNCTION()
	void DamageTaked(float DamageValue);
public:
	virtual void TakeDamage(FDamageData DamageData) override;
	virtual void ScoreUp(float Score) override;
	virtual void MoveForward(float AxisValue);
	virtual void MoveLeft(float AxisValue);
	void MovePawn(float DeltaTime);
	void RotatePawn(float DeltaTime);
	void Fire();
	void SetupCannon(TSubclassOf<ACannon> cannon);
	UTexture2D* GetPopUpImage(){return PopUpPic;}
	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);
protected:
	float _targetForwardAxisValue;
	float _targetLeftAxisValue;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float InterpolationKey = 0.03f;
	float interpolatedYaw;
	float TurretRotationInterpolationKey=0.1f;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float RotationSpeed = 100.0f;
//AI
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Target Points" , Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> TargetPoints;	
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
	TArray<FVector> GetTargetingPoints();
	void SetTargetPoints(TArray<ATargetPoint*> NewPatrollingPoints);
	UFUNCTION()
	FVector GetTurretForwardVector();
	FVector GetEyesPosition();
};
