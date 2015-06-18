// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "ProjectMishkanPlayerController.h"
#include "EngineUtils.h"

const FString AProjectMishkanPlayerController::MainCameraName = TEXT("MainCamera");
const FString AProjectMishkanPlayerController::PlacementCameraName = TEXT("PlacementCamera");
const FString AProjectMishkanPlayerController::FirstPersonCameraName = TEXT("FirstPersonCamera");

AProjectMishkanPlayerController::AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

// Called every Frame
void AProjectMishkanPlayerController::PlayerTick(float deltaTime)
{
	Super::PlayerTick(deltaTime);
}

// Listens for player input and binds the appropriate functions
void AProjectMishkanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	InputComponent->BindAction("SwitchToMainCamera", IE_Released, this, &AProjectMishkanPlayerController::ChangeToMainCamera);
	InputComponent->BindAction("SwitchToPlacementCamera", IE_Released, this, &AProjectMishkanPlayerController::ChangeToPlacementCamera);
	InputComponent->BindAction("SwitchToFirstPersonCamera", IE_Released, this, &AProjectMishkanPlayerController::ChangeToFirstPersonCamera);
	InputComponent->BindAction("RotateLeft", IE_Released, this, &AProjectMishkanPlayerController::RotateLeft);
	InputComponent->BindAction("RotateRight", IE_Released, this, &AProjectMishkanPlayerController::RotateRight);
}

// Start placing the selected Vessel
void AProjectMishkanPlayerController::SelectPlaceable(IPlaceable* placeable)
{
	Placeable = placeable;
	ChangeToPlacementCamera();
}

// Lazy loads Main Camera pointer
FORCEINLINE ACameraActor* AProjectMishkanPlayerController::GetMainCamera()
{
	if (MainCamera == NULL) {
		return GetCamera(MainCameraName);
	}
	return MainCamera;
}

// Lazy loads Main Camera pointer
FORCEINLINE ACameraActor* AProjectMishkanPlayerController::GetPlacementCamera()
{
	if (PlacementCamera == NULL) {
		return GetCamera(PlacementCameraName);
	}
	return PlacementCamera;
}

// Lazy loads Main Camera pointer
FORCEINLINE ACameraActor* AProjectMishkanPlayerController::GetFirstPersonCamera()
{
	if (FirstPersonCamera == NULL) {
		return GetCamera(FirstPersonCameraName);
	}
	return FirstPersonCamera;
}

// Looks for the CameraActor pointer with the given name. Returns NULL if not found
FORCEINLINE ACameraActor* AProjectMishkanPlayerController::GetCamera(const FString& Name)
{
	for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == Name) {
			return *ActorItr;
		}
	}
	return NULL;
}

// Input handlers
void AProjectMishkanPlayerController::ChangeToMainCamera(float Value)
{
	ChangeToMainCamera();
}

void AProjectMishkanPlayerController::ChangeToPlacementCamera(float Value)
{
	ChangeToPlacementCamera();
}

void AProjectMishkanPlayerController::ChangeToFirstPersonCamera(float Value)
{
	ChangeToFirstPersonCamera();
}

void AProjectMishkanPlayerController::RotateLeft()
{
	if (Placeable != NULL) {
		Placeable->RotateLeft();
	}
}

void AProjectMishkanPlayerController::RotateRight()
{
	if (Placeable != NULL) {
		Placeable->RotateRight();
	}
}

// Helper functions to switch the current camera
void AProjectMishkanPlayerController::ChangeToMainCamera()
{
	ChangeToCamera(MainCameraName);
	Placeable = NULL;	// If we're keeping track of a Placeable, stop
}

void AProjectMishkanPlayerController::ChangeToPlacementCamera()
{
	ChangeToCamera(PlacementCameraName);
}

void AProjectMishkanPlayerController::ChangeToFirstPersonCamera()
{
	ChangeToCamera(FirstPersonCameraName);
}

void AProjectMishkanPlayerController::ChangeToCamera(const FString& Name)
{
	ACameraActor* camera = GetCamera(Name);
	if (camera != NULL) {
		SetViewTarget(camera);
	}
}