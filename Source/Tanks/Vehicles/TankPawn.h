// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Arm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;	
	ATankPawn();
	
	void FireSpecial();
	void ChangeWeapon();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	
};
