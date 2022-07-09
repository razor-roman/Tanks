// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ATurret::ATurret()
{
	WidgetComp->SetRelativeRotation(FRotator(0,0,-90));
	WidgetComp->SetRelativeLocation(FVector(0,-220,0));
	WidgetComp->SetupAttachment(CannonSetupPoint);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyVisualAsset(TEXT("StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'"));
	if(BodyVisualAsset.Succeeded())
	{ 
		Body->SetStaticMesh(BodyVisualAsset.Object);
		Body->SetRelativeLocation(FVector(0,0,0));
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretVisualAsset(TEXT("StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'"));
	if(TurretVisualAsset.Succeeded())
	{
		Turret->SetStaticMesh(TurretVisualAsset.Object);
		Turret->SetRelativeLocation(FVector(0,0,270));
		Turret->SetRelativeRotation(FRotator(0,0,90));
	}
	HitCollider->AddRelativeLocation(FVector(0,0,140));
	HitCollider->SetBoxExtent(FVector(150,150,150));
	HitCollider->SetCollisionProfileName("Tank");
	CannonSetupPoint->SetRelativeLocation(FVector(180,-40,20));
	OnDestroyParticleEffect->SetRelativeLocation(FVector(0,0,260));
	OnDestroyParticleEffect->SetRelativeScale3D(FVector(3,3,3));
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret::Destroyed()
{
	Super::Destroyed();
}