// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/Controllers/TankPawnThirdPersonController.h"

void UActorSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor=nullptr;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
}

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (DraggedText)
	{
		DraggedText->SetText(DraggedName);
	}
}

void UActorSpawnerWidget::NativeConstruct()
{	
	Super::NativeConstruct();
	//GetOwningPlayer()
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if(ATankPawnThirdPersonController* MyController = Cast<ATankPawnThirdPersonController>(PlayerController))
	{
		MyController->OnMouseButtonUp.AddUObject(this,&ThisClass::OnMouseButtonUp);
	}
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
		PlayerController->SetShowMouseCursor(true);
	}
	return FReply::Handled();
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(SpawnedActor && PlayerController)
	{
		FVector WorldMouseLocation;
		FVector WorldMouseDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldMouseLocation,WorldMouseDirection);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		FHitResult OutHit;
		constexpr float Dist = 100000.f;
		GetWorld()->LineTraceSingleByChannel(OutHit,WorldMouseLocation,WorldMouseLocation+WorldMouseDirection*Dist,
			ECollisionChannel::ECC_WorldStatic,Params);
		if(OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}
	}
}
