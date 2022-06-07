// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLoader.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMapLoader::AMapLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent * sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	GatesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gates Mesh"));	
	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Activated lights"));
	DeactivatedLight =	CreateDefaultSubobject<UPointLightComponent>(TEXT("Deactivated lights"));
	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger collider"));
	
	GatesMesh->SetupAttachment(sceneComp);
	ActivatedLight->SetupAttachment(sceneComp);
	DeactivatedLight->SetupAttachment(sceneComp);
	TriggerCollider->SetupAttachment(sceneComp);
	
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this,&AMapLoader::OnTriggerOverlapBegin);
	
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	IsActivated = NewIsActivated;
	SetActiveLights();
}

// Called when the game starts or when spawned
void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActiveLights();

}

// Called every frame
void AMapLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapLoader::SetActiveLights()
{
	ActivatedLight->SetHiddenInGame(!IsActivated);
	DeactivatedLight->SetHiddenInGame(IsActivated);
}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!IsActivated)
    return;
    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(OtherActor == PlayerPawn)
    {
    UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);    	
    }

}

