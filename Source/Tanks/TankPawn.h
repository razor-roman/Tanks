// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <vector>

#include "Cannon.h"
#include "CoreMinimal.h"
#include "CommonClass.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"


class UArrowComponent;
class AMyPlayerController;
class ACannon;

/**
 * 
 */
UCLASS()
class TANKS_API ATankPawn : public ACommonClass
{
	GENERATED_BODY()
public:
	UPROPERTY()
	AMyPlayerController* TankController;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float RotationSpeed = 100.0f;
	
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Arm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;	
	ATankPawn();
	void Tick(float DeltaTime) override;
	
	float interpolatedYaw;
	void FireSpecial();
	void SetupCannon(TSubclassOf<ACannon> cannon);
	void ChangeWeapon();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
	TSubclassOf<ACannon> FirstCannon;
	UPROPERTY()
	TSubclassOf<ACannon> SecondCannon;
	bool first=true;
	
};
