// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "GameFramework/PlayerController.h"
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
protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveLeftRight(float AxisValue);
public:
	virtual void SetupInputComponent() override;
};
