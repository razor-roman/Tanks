// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonClass.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawnThirdPerson.generated.h"

class ATankPawnThirdPersonController;
/**
 * 
 */
UCLASS(Abstract)
class TANKS_API ATankPawnThirdPerson : public ACommonClass
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ATankPawnThirdPersonController* TankController;	
	
protected:
	
	float CurrentRightAxisValue;
	UPROPERTY(EditAnywhere)
	float TurretAngleMax = 45.0f;
	float TurretAngleMin = -15.0f;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Arm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	ATankPawnThirdPerson();
	virtual void BeginPlay() override;
	void Tick(float DeltaTime) override;
	float _targetForwardAxisValue;
	float _targetLeftAxisValue;
	float _targetTurn;
	float _targetLookUp;	
public:
	UFUNCTION()
	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void FireSpecial();
};
