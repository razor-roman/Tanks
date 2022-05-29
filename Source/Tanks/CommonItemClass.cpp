// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonItemClass.h"

// Sets default values
ACommonItemClass::ACommonItemClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this,&ACommonItemClass::OnMeshOverlapBegin);
}

// Called when the game starts or when spawned
void ACommonItemClass::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACommonItemClass::Floating(float DeltaTime)
{
	FVector newLocation = GetActorLocation();
	FRotator newRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime-DeltaTime)- FMath::Sin(RunningTime));
	newLocation.Z+=DeltaHeight*FloatSpeed;
	float DeltaRotation = DeltaTime * RotationSpeed;
	newRotation.Yaw +=DeltaRotation;
	SetActorLocationAndRotation(newLocation,newRotation);
}

void ACommonItemClass::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		Destroy();
}

// Called every frame
void ACommonItemClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bFloating==true) Floating(DeltaTime);
}

