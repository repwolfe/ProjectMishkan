// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "ProjectMishkanGameMode.h"
#include "ProjectMishkanPlayerController.h"

AProjectMishkanGameMode::AProjectMishkanGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AProjectMishkanPlayerController::StaticClass();
}
