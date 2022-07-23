// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonClass.h"

#include "ChaosInterfaceWrapperCore.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACommonClass::ACommonClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Turret=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLIDER"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HEALTH"));
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	OnDestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("OnDestroyAudioEffect"));
	OnDestroyParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnDestroyParticleEffect"));
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	//WidgetInteract = CreateDefaultSubobject<UWidgetInteractionComponent>("Widget Interact");
	
	// UUserWidget* TestWidget = CreateWidget(this,HealthWidget);
	// WidgetComp->SetWidget(TestWidget);
	//
	// WidgetComp->GetWidget();
	//
	RootComponent=Body;
	//Body->SetupAttachment(RootComponent);
	Turret->SetupAttachment(Body);
	HitCollider->SetupAttachment(RootComponent);
	CannonSetupPoint->AttachToComponent(Turret,FAttachmentTransformRules::KeepRelativeTransform);
	OnDestroyAudioEffect->SetupAttachment(Body);
	OnDestroyParticleEffect->SetupAttachment(Body);
	WidgetComp->SetupAttachment(Turret);
	
	HealthComponent->OnDie.AddUObject(this,&ACommonClass::Die);
	HealthComponent->OnDamaged.AddUObject(this,&ACommonClass::DamageTaked);
	
	OnDestroyAudioEffect->SetAutoActivate(false);
	OnDestroyParticleEffect->SetAutoActivate(false);
	HitCollider->SetBoxExtent(FVector(150,150,50));
	WidgetComp->SetRelativeScale3D(FVector(1,1,0.5));
}

// Called when the game starts or when spawned
void ACommonClass::BeginPlay()
{
	Super::BeginPlay();
	if(CannonClass) SetupCannon(CannonClass);
	HealthComponent->SetHealth(Health);
	PlayerStart=GetActorLocation();
	WidgetComp->SetWidgetClass(HealthWidget);	
	auto WidClass = WidgetComp->GetWidget();
	HealthBar = Cast<UHealthBar>(WidClass);
	if(!HealthBar) UE_LOG(LogTemp, Warning, TEXT("No HealthBar"));
	
	// WidgetInteract->PressKey(FKey());
	// WidgetInteract->PressPointerKey(FKey());
}

void ACommonClass::Destroyed()
{
	Super::Destroyed();
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
	UE_LOG(LogTemp, Warning, TEXT("ACommonClass::Die"));
	OnDestroyParticleEffect->ActivateSystem();
	OnDestroyAudioEffect->Play();	
	/*if(!Controller->IsPlayerController() && Controller) // TODO Controller Error when collapse with projectle.
	{
		Controller->Destroy();
		MoveLeft(0);
		Body->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Ignore);
		HitCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Ignore);
	}
	else*/
	{		
		SetActorLocation(PlayerStart);
		HealthComponent->SetHealth(1);
		OnDestroyParticleEffect->Deactivate();
		OnDestroyAudioEffect->Stop();
		bIsDead = true;
	}
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
	if (HealthBar) HealthBar->SetHealthBarChange(HealthComponent->GetHealth()/HealthComponent->MaxHealth);
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No HealthBar"));
	}
}

void ACommonClass::ScoreUp(float Score)
{
	ScoreNumber+=Score;
}

void ACommonClass::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ACommonClass::MoveLeft(float AxisValue)
{
				
	_targetLeftAxisValue = AxisValue;
}

void ACommonClass::MovePawn(float DeltaTime)
{
	FVector currentLocation = Body->GetRelativeLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation+forwardVector*MoveSpeed*_targetForwardAxisValue*DeltaTime;
	Body->SetRelativeLocation(movePosition,true);
}

void ACommonClass::RotatePawn(float DeltaTime)
{
	//interpolatedYaw = FMath::Lerp(interpolatedYaw,_targetLeftAxisValue,InterpolationKey);
	float yawRotation = RotationSpeed * _targetLeftAxisValue * DeltaTime;
	FRotator bodyCurrentRotation = Body->GetRelativeRotation();	
	float bodyRotation = bodyCurrentRotation.Yaw+yawRotation;	
	Body->SetRelativeRotation(FRotator(0,bodyRotation,0));	
}

void ACommonClass::Fire()
{
	if(Cannon) Cannon->Fire();
}

void ACommonClass::SetupCannon(TSubclassOf<ACannon> cannon)
{
	/*if(FirstCannon==NULL)
	{		
		FirstCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("FirstCannon %f"),SecondCannon.GetDefaultObject());
	}
	else if(cannon!=FirstCannon)
	{		
		SecondCannon=cannon;
		UE_LOG(LogTemp, Warning, TEXT("SecondCannon %f"),FirstCannon.GetDefaultObject());
	}*/
	if(Cannon)
	{
		Cannon->Destroy();		
	}	
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(cannon, params);	
	Cannon->AttachToComponent(CannonSetupPoint,FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}


void ACommonClass::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(Turret->GetComponentLocation(), TargetPosition);
	FRotator currRotation = Turret->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	Turret->SetWorldRotation(targetRotation);
	//Turret->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	DrawDebugLine(GetWorld(), CannonSetupPoint->GetComponentLocation(), TargetPosition, FColor::Cyan, false, 1.0f, 0, 10);
}

TArray<FVector> ACommonClass::GetTargetingPoints()
{
	TArray<FVector> points;
	for (ATargetPoint* point: TargetPoints)
	{
		points.Add(point->GetActorLocation());
	}
	return points;
}

void ACommonClass::SetTargetPoints(TArray<ATargetPoint*> NewTargetPoints)
{
	TargetPoints = NewTargetPoints;
}

FVector ACommonClass::GetTurretForwardVector()
{
	return  Turret->GetForwardVector();
}

FVector ACommonClass::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}


