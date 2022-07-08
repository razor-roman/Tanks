// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

void UHealthBar::HealthBarChange(float Health)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthBarChange %f"),Health);
	HealthBar->Percent = Health;
}
