// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMainMenuGameMode(const FObjectInitializer& ObjectInitializer);
};



