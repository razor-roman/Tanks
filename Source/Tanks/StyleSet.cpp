#include "StyleSet.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__ )


TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
{
	//TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("StyleSet"),	ScopeToDirectory, ScopeToDirectory);
	FString Path = FPaths::ProjectContentDir() / TEXT("/UI");
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"),Path,Path);

	Style->Set("Red",FLinearColor::Red);
	Style->Set("DefaultPadding",FMargin(5.f));
	//Style->Set("Frog",new IMAGE_BRUSH("darth-vader-icon-256", FVector2D(256.0f, 256.0f)));
	return Style;
}

TSharedPtr<ISlateStyle> FStyleSet::StylePtr = NULL;

void FStyleSet::Initialize()
{
	Shutdown();
	StylePtr = FindStyle("/Game/Widget/Styles/");
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}
void FStyleSet::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		ensure(StylePtr.IsUnique());
		StylePtr.Reset();
	}
}
const ISlateStyle& FStyleSet::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}