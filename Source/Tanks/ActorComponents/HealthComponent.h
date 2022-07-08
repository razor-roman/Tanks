// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tanks/GameStructs.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_EVENT(UHealthComponent,FOnDie)
	DECLARE_EVENT_OneParam(UHealthComponent,FOnHealthChanged,float)
public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="MaxHealth value")
	float MaxHealth= 10;
protected:
	UPROPERTY(BlueprintReadWrite,Category=" CurrentHealth value")
	float CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FOnDie OnDie;
	FOnHealthChanged OnDamaged;

	void TakeDamage(FDamageData DamageData);
	UFUNCTION()
	float GetHealth() const;
	float GetHealthState() const;
	void AddHealth(float AdditionalHealthValue);
	void SetHealth(float Health);	
	UPROPERTY()
	bool Died=false;
};
	
