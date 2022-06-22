// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonItemClass.generated.h"

UCLASS()
class TANKS_API ACommonItemClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommonItemClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	UStaticMeshComponent* Mesh;
		
	void Floating(float DeltaTime);
	UFUNCTION()
	virtual void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
	FHitResult& SweepResult) ;
	
	UPROPERTY(EditAnywhere);
	bool bFloating;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FloatingActor")
	float FloatSpeed=20.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FloatingActor")
	float RotationSpeed=20.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
