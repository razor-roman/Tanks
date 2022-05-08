// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonClass.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankPawn : public ACommonClass
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere,Category="Movement|Speed")
	float RotationSpeed = 100.0f;
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
