// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "ProjectMishkanPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AProjectMishkanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer);
};


