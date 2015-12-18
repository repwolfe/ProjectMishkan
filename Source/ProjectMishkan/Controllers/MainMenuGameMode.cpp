// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "MainMenuGameMode.h"
#include "MainMenuPlayerController.h"
//#include "../GameObjects/MishkanHUD.h"

AMainMenuGameMode::AMainMenuGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	//HUDClass = AMishkanHUD::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
