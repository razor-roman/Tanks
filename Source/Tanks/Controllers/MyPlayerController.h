// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tanks/Vehicles/TankPawn.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	ATankPawn* TankPawn;
	AMyPlayerController();
	UPROPERTY()
	FVector MousePos;
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
	virtual void  MoveForward(float AxisValue);
	virtual void MoveLeftRight(float AxisValue);
	void Fire();
	void FireSpecial();
	void ChangeWeapon();
public:
	FVector GetMousePos() {return MousePos;};
	virtual void SetupInputComponent() override;
	
};
