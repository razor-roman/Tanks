// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"
#include "IImageWrapper.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/Controllers/TankPawnThirdPersonController.h"

void UActorSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor=nullptr;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
}

void UActorSpawnerWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogActor,Warning,TEXT("ENTER"));
	Panel->SetVisibility(ESlateVisibility::Visible);
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UActorSpawnerWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogActor,Warning,TEXT("LEAVE"));
	Panel->SetVisibility(ESlateVisibility::Hidden);
	Super::NativeOnMouseLeave(InMouseEvent);
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
	Panel->SetVisibility(ESlateVisibility::Hidden);	;
	TextPopUp->SetText(FText::FromString(SpawnedActor->GetName()));
	/*ACommonClass* CommonClass = Cast<ACommonClass>(SpawnedActor->GetClass());
	if(!CommonClass)
	{
		UE_LOG(LogActor,Warning,TEXT("!CommonClass"));
	}
	else CommonClass->GetPopUpImage();*/
	//ImagePopUp->SetBrushFromTexture();
	
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FActorSpawnParameters param;
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass,param); // TODO not at an Actor Location
		//SpawnedActor->SetActorLocation(FVector(1000,1000,1000));
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
