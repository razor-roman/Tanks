// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBox.h"

#include "TankPawn.h"

AWeaponBox::AWeaponBox()
{
	
}

void AWeaponBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMeshOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	ATankPawn * playerPawn = Cast<ATankPawn>(OtherActor);
	if(playerPawn->GetPatrollingPoints().Num()==0)
	{		
		playerPawn->SetupCannon(CannonClass);
		Destroy();
	}
}
