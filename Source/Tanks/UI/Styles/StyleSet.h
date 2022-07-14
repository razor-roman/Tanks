#pragma once
#include "Slate.h"
struct TANKS_API FStyleSet
{
public:
	static void Initialize();
	static void Shutdown();
	
	static const ISlateStyle& Get();
private:
	static TSharedPtr<class ISlateStyle> StylePtr;	
};
