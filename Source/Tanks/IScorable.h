// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IScorable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIScorable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKS_API IIScorable
{
	GENERATED_BODY()
public:
	virtual void ScoreUp(float Score) = 0; 
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
