// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonClass.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"


class AMyPlayerController;
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
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float InterpolationKey = 0.1f;
	float CurrentRightAxisValue;
	UPROPERTY(BlueprintReadWrite)
	USpringArmComponent* Arm;
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;
public:
	ATankPawn();
	void Tick(float DeltaTime) override;
	float _targetForwardAxisValue;
	float _targetLeftAxisValue;
	UFUNCTION()
	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);
};
