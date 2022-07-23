// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tanks/UI/MyHUD.h"
#include "Tanks/Vehicles/TankPawnThirdPerson.h"
#include "TankPawnThirdPersonController.generated.h"

class UWidgetBlueprintLibrary;
/**
 * 
 */
UCLASS()
class TANKS_API ATankPawnThirdPersonController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UInventoryComponent * InventoryComponent;
	UPROPERTY()
	UInventoryManagerComponent * InventoryManagerComponent;
	UPROPERTY()
	ATankPawnThirdPerson* TankPawn;
	UPROPERTY()
	AMyHUD* HUD;
	UPROPERTY()
	APlayerController* PC;
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
	void MainMenu();
	void Inventory();
	void DragAndDrop();
	void SetWidget(EWidgetID Widget, bool bRemotePrevious,int ZOrder=0);
public:
	FVector GetMousePos() {return MousePos;};
	void OnLeftMouseButtonUp();
	virtual void SetupInputComponent() override;	
	FSimpleMulticastDelegate OnMouseButtonUp;
};
