// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "CommonClass.generated.h"

UCLASS()
class TANKS_API ACommonClass : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:
	// Sets default values for this pawn's properties
	ACommonClass();
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Turret;
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitCollider;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	UHealthComponent* HealthComponent;
	float Health=1;	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION()
	void Die();
	UFUNCTION()
	void DamageTaked(float DamageValue);
public:
	virtual void TakeDamage(FDamageData DamageData) override;
};
