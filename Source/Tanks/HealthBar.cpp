// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

void UHealthBar::SetHealthBarChange(float Health)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthBarChange %f"),Health);
	HealthBar->SetPercent(Health);
}

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	HealthBar->SetPercent(1);
}
