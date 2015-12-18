// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
//#include "../GameObjects/MishkanHUD.h"
#include "MainMenuPlayerController.h"
#include "EngineUtils.h"

AMainMenuPlayerController::AMainMenuPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

/*
// Called when the HUD is changed
void AProjectMishkanPlayerController::ClientSetHUD_Implementation(TSubclassOf< class AHUD > NewHUDClass)
{
	Super::ClientSetHUD_Implementation(NewHUDClass);

	// If it's MishkanHUD
	AMishkanHUD* HUD = Cast<AMishkanHUD>(GetHUD());
	if (HUD) {
		FHUDButtonDelegate handlers[EPlacementButton::Size];
		handlers[EPlacementButton::RotateLeft].BindUObject(this, &AProjectMishkanPlayerController::RotateLeft);
		handlers[EPlacementButton::RotateRight].BindUObject(this, &AProjectMishkanPlayerController::RotateRight);
		handlers[EPlacementButton::Okay].BindUObject(this, &AProjectMishkanPlayerController::AttemptPlacement);
		handlers[EPlacementButton::Cancel].BindUObject(this, &AProjectMishkanPlayerController::CancelPlacement);
		HUD->SetPlacementHandlers(handlers);
		HUD->OnNewOwningPlayerController(this);
	}
}
*/

// Called every Frame
void AMainMenuPlayerController::PlayerTick(float deltaTime)
{
	Super::PlayerTick(deltaTime);
}

// Listens for player input and binds the appropriate functions
void AMainMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	//InputComponent->BindAction("StartGame", IE_Released, this, &AMainMenuPlayerController::StartGame);
}

void AMainMenuPlayerController::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("FunctionalityTest"));
}