// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

UCLASS()
class AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController(const FObjectInitializer& ObjectInitializer);

	//virtual void ClientSetHUD_Implementation(TSubclassOf< class AHUD > NewHUDClass) override;
	virtual void PlayerTick(float deltaTime) override;

private:
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable, Category="OnClick")
	void StartGame();
};