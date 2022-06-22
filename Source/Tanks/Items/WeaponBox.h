// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Cannon.h"
#include "CommonItemClass.h"
#include "WeaponBox.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AWeaponBox : public ACommonItemClass
{
	GENERATED_BODY()
protected:
	AWeaponBox();
	virtual void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere);
	TSubclassOf<ACannon> CannonClass;
};
