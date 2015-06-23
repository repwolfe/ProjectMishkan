// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "ProjectMishkanPlayerController.h"
#include "EngineUtils.h"

const FString AProjectMishkanPlayerController::MainCameraName = TEXT("MainCamera");
const FString AProjectMishkanPlayerController::PlacementCameraName = TEXT("PlacementCamera");
const FString AProjectMishkanPlayerController::FirstPersonCameraName = TEXT("FirstPersonCamera");

AProjectMishkanPlayerController::AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), BuildMode(EBuildMode::Selection)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

// Called every Frame
void AProjectMishkanPlayerController::PlayerTick(float deltaTime)
{
	// If in placement mode, check if mouse pressed and dragged, move camera/placeable
	if (BuildMode == EBuildMode::Placement && MousePressed) {
		const uint8 SCALE_VALUE = 5;
		float deltaX = 0, deltaY = 0;
		GetInputMouseDelta(deltaX, deltaY);		// TODO: Make work for touch screen

		FVector loc = Placeable->GetLocation();
		loc.X += deltaY * SCALE_VALUE;		// Mouse coordinates and World coordinates are transpose of each other
		loc.Y += deltaX * SCALE_VALUE;
		Placeable->SetLocation(loc);

		ACameraActor* camera = GetPlacementCamera();
		FVector cameraLoc = camera->GetActorLocation();
		cameraLoc.X = loc.X;
		cameraLoc.Y = loc.Y;
		camera->SetActorLocation(cameraLoc);
	}

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
	InputComponent->BindAction("OnPress", IE_Pressed, this, &AProjectMishkanPlayerController::OnPress);
	InputComponent->BindAction("OnRelease", IE_Released, this, &AProjectMishkanPlayerController::OnRelease);
	InputComponent->BindAction("CancelPlacement", IE_Released, this, &AProjectMishkanPlayerController::CancelPlacement);
}

// Start placing the selected Vessel
void AProjectMishkanPlayerController::SelectPlaceable(IPlaceable* placeable)
{
	Placeable = placeable;
	PlaceableLocation = Placeable->GetLocation();
	ChangeToPlacementCamera();

	// Update the camera's X/Y coordinates (but not Z) to the Placeable's location
	ACameraActor* camera = GetPlacementCamera();
	FVector cameraLoc = camera->GetActorLocation();
	cameraLoc.X = PlaceableLocation.X;
	cameraLoc.Y = PlaceableLocation.Y;
	camera->SetActorLocation(cameraLoc);

	BuildMode = EBuildMode::Placement;
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

// Event handlers
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
	if (BuildMode == EBuildMode::Placement) {
		Placeable->RotateLeft();
	}
}

void AProjectMishkanPlayerController::RotateRight()
{
	if (BuildMode == EBuildMode::Placement) {
		Placeable->RotateRight();
	}
}

void AProjectMishkanPlayerController::OnPress()
{
	MousePressed = true;
}

void AProjectMishkanPlayerController::OnRelease()
{
	MousePressed = false;
}

void AProjectMishkanPlayerController::PlaceCurrent()
{
	ChangeToMainCamera();
	BuildMode = EBuildMode::Selection;
}

void AProjectMishkanPlayerController::CancelPlacement()
{
	ChangeToMainCamera();
	if (BuildMode == EBuildMode::Placement) {
		Placeable->SetLocation(PlaceableLocation);
		Placeable = NULL;
		BuildMode = EBuildMode::Selection;
	}
}

// Helper functions to switch the current camera
void AProjectMishkanPlayerController::ChangeToMainCamera()
{
	ChangeToCamera(MainCameraName);
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