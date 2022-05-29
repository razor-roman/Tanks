// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonItemClass.h"
#include "AmmoBox.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AAmmoBox : public ACommonItemClass
{
	GENERATED_BODY()
protected:
	AAmmoBox();
	virtual void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileCount=10;
	float TraceCount=10;
};
