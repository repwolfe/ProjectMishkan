// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "ProjectMishkanGameMode.h"
#include "ProjectMishkanPlayerController.h"
#include "../Model/StringConstants.h"
#include "../GameObjects/MishkanHUD.h"

AProjectMishkanGameMode::AProjectMishkanGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	HUDClass = AMishkanHUD::StaticClass();
	PlayerControllerClass = AProjectMishkanPlayerController::StaticClass();
	StringConstants::Initialize();
}
