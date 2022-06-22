// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsProjectile.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

APhysicsProjectile::APhysicsProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicsComponent"));
    TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail effect"));
    TrailEffect->SetupAttachment(Mesh);
}

void APhysicsProjectile::Start(FVector StartPos,FRotator ForwardVector)
{	
	FVector actorLocation;
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();	
		MoveVector = GetActorForwardVector() * TrajectorySimulationSpeed;
		CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(),MoveVector, TrajectorySimulationMaxTime, TrajectorySimulationTimeStep, 0);
	
	if(ShowTrajectory)
	{
		for(FVector position: CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, FColor::Purple, true, 1, 0,
			2);
		}
	}
	TragectoryPointIndex = 0;
	Super::Start(FVector().ZeroVector,FRotator().ZeroRotator);
}

void APhysicsProjectile::Move()
{
	Super::Move();
	FVector currentMoveVector = CurrentTrajectory[TragectoryPointIndex] - GetActorLocation();
	currentMoveVector.Normalize();
	FVector newLocation = GetActorLocation() + currentMoveVector * MoveSpeed * MoveRate;
	SetActorLocation(newLocation);
	if(FVector::Distance(newLocation, CurrentTrajectory[TragectoryPointIndex]) <= MoveAccurency)
	{
		TragectoryPointIndex++;
		if(TragectoryPointIndex >= CurrentTrajectory.Num()-1) // FIX IT
		{
			Explode();
			Destroy();
			SetLifeSpan(0);
		}			
		else
		{
			FRotator newRotation =
			UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			CurrentTrajectory[TragectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}

void APhysicsProjectile::Explode()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);
	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";
    TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;
	bool sweepResult = GetWorld()->SweepMultiByChannel
    (
	    AttackHit,
	    startPos,
	    endPos,
	    Rotation,
	    ECollisionChannel::ECC_Visibility,
	    Shape,
	    params
    );
	GetWorld()->DebugDrawTraceTag = "Explode Trace";
	if(sweepResult)
	{
		for(FHitResult hitResult: AttackHit)
		{
			CheckDamageOrPush(hitResult);
		}
	}
}
