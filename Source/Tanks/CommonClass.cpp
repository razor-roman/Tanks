// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonClass.h"

// Sets default values
ACommonClass::ACommonClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Turret=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLIDER"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HEALTH"));
	
	RootComponent=Body;
	Body->SetupAttachment(RootComponent);
	Turret->SetupAttachment(Body);
	HitCollider->SetupAttachment(RootComponent);
	
	HealthComponent->OnDie.AddUObject(this,&ACommonClass::Die);
	HealthComponent->OnDamaged.AddUObject(this,&ACommonClass::DamageTaked);
	
}

// Called when the game starts or when spawned
void ACommonClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommonClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACommonClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACommonClass::Die()
{
	Destroy();
}

void ACommonClass::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(),
DamageValue, HealthComponent->GetHealth());
}

void ACommonClass::TakeDamage(FDamageData DamageData)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f "), *GetName(),DamageData.DamageValue);
	HealthComponent->TakeDamage(DamageData);
}

