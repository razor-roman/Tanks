// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "MainMenuButtonWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct TANKS_API FMainMenuButtonStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FMainMenuButtonStyle();
	virtual ~FMainMenuButtonStyle();
	/** Style of check boxes */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle ButtonStyle;
	/** Style of options text */

	
	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMainMenuButtonStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UMainMenuButtonWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FButtonStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
