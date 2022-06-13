// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawnThirdPerson.h"
#include "GameFramework/PlayerController.h"
#include "TankPawnThirdPersonController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankPawnThirdPersonController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	ATankPawnThirdPerson* TankPawn;
	ATankPawnThirdPersonController();
	UPROPERTY()
	FVector MousePos;
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveLeftRight(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);	
	void Fire();
	void FireSpecial();
public:
	FVector GetMousePos() {return MousePos;};
	virtual void SetupInputComponent() override;
};
