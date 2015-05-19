// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "ProjectMishkanGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AProjectMishkanGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProjectMishkanGameMode(const FObjectInitializer& ObjectInitializer);
};



