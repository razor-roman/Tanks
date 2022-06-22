// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"

#include "Tanks/Vehicles/TankPawn.h"


AAmmoBox::AAmmoBox()
{
	
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMeshOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	ATankPawn * playerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(OtherActor==playerPawn)
	{
		playerPawn->Cannon->AddProjectile(ProjectileCount);
		playerPawn->Cannon->AddTrace(TraceCount);
	}
}
