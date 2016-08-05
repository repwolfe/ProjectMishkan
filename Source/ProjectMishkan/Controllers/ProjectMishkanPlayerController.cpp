// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "../GameObjects/MishkanHUD.h"
#include "ProjectMishkanPlayerController.h"
#include "EngineUtils.h"

const FString AProjectMishkanPlayerController::PlayerPawnName = TEXT("PlayerPawn");
const FString AProjectMishkanPlayerController::MainCameraName = TEXT("MainCamera");
const FString AProjectMishkanPlayerController::PlacementCameraName = TEXT("PlacementCamera");

AProjectMishkanPlayerController::AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), BuildMode(EBuildMode::Selection)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	BuildOrder = NewObject<UBuildOrder>(this, TEXT("BuildOrder"));
}

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
		handlers[EPlacementButton::Cancel].BindUObject(this, &AProjectMishkanPlayerController::OnCancelButtonClicked);
		HUD->SetPlacementHandlers(handlers);
		HUD->OnNewOwningPlayerController(this);
	}
}

// Called every Frame
void AProjectMishkanPlayerController::PlayerTick(float deltaTime)
{
	// Initialize pointers to world objects
	if (CurrentCamera == NULL) {
		ChangeToMainCamera();		// At the start use the main camera
		SetBuildMode(EBuildMode::Selection);
	}
	if (PlayerPawn == NULL) {
		PlayerPawn = GetActorInWorld<AMishkanPawn>(PlayerPawnName);
	}

	// Get the mouse delta
	const uint8 SCALE_VALUE = 20;	// TODO: Move this somewhere else, and pick a good value
	float mouseDeltaX = 0, mouseDeltaY = 0;
	GetInputMouseDelta(mouseDeltaX, mouseDeltaY);		// TODO: Make work for touch screen
	mouseDeltaX *= SCALE_VALUE; mouseDeltaY *= SCALE_VALUE;

	if (BuildMode == EBuildMode::Character) {
		PlayerPawn->UpdateSight(mouseDeltaX, mouseDeltaY);

		// Check if holding movement keys
		if (PressingForward) { PlayerPawn->MoveForward(); }
		if (PressingBack) { PlayerPawn->MoveBack(); }
		if (PressingLeft) { PlayerPawn->MoveLeft(); }
		if (PressingRight) { PlayerPawn->MoveRight(); }
	}
	// If in selection/placement mode, check if mouse pressed and dragged, move camera/placeable
	else if (MousePressed) {
		// Move the camera as the player drags

		// Mouse coordinates and World coordinates are transpose of each other
		FVector2D delta(mouseDeltaY, mouseDeltaX);

		if (BuildMode == EBuildMode::Selection || BuildMode == EBuildMode::Placement) {
			FVector cameraLoc = CurrentCamera->GetActorLocation();
			cameraLoc.X += delta.X;
			cameraLoc.Y += delta.Y;
			CurrentCamera->SetActorLocation(cameraLoc);
		}
		if (BuildMode == EBuildMode::Placement) {
			FVector loc = Placeable->GetLocation();
			loc.X += delta.X;
			loc.Y += delta.Y;
			Placeable->SetLocation(loc);
		}
	}
	Super::PlayerTick(deltaTime);
}

// Listens for player input and binds the appropriate functions
void AProjectMishkanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	InputComponent->BindAction("SwitchToCharacterMode", IE_Released, this, &AProjectMishkanPlayerController::SwitchToCharacterMode);
	InputComponent->BindAction("SwitchToSelectionMode", IE_Released, this, &AProjectMishkanPlayerController::SwitchToSelectionMode);
	InputComponent->BindAction("RotateLeft", IE_Released, this, &AProjectMishkanPlayerController::RotateLeft);
	InputComponent->BindAction("RotateRight", IE_Released, this, &AProjectMishkanPlayerController::RotateRight);
	InputComponent->BindAction("OnPress", IE_Pressed, this, &AProjectMishkanPlayerController::OnPress);
	InputComponent->BindAction("OnRelease", IE_Released, this, &AProjectMishkanPlayerController::OnRelease);
	InputComponent->BindAction("AttemptPlacement", IE_Released, this, &AProjectMishkanPlayerController::AttemptPlacement);
	InputComponent->BindAction("CancelPlacement", IE_Released, this, &AProjectMishkanPlayerController::CancelPlacement);

	InputComponent->BindAction("ToggleHidePlaceables", IE_Released, this, &AProjectMishkanPlayerController::ToggleHidePlaceables);

	InputComponent->BindAction("MoveForward", IE_Pressed, this, &AProjectMishkanPlayerController::PressedForward);
	InputComponent->BindAction("MoveBack", IE_Pressed, this, &AProjectMishkanPlayerController::PressedBack);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AProjectMishkanPlayerController::PressedLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &AProjectMishkanPlayerController::PressedRight);
	InputComponent->BindAction("MoveForward", IE_Released, this, &AProjectMishkanPlayerController::ReleasedForward);
	InputComponent->BindAction("MoveBack", IE_Released, this, &AProjectMishkanPlayerController::ReleasedBack);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &AProjectMishkanPlayerController::ReleasedLeft);
	InputComponent->BindAction("MoveRight", IE_Released, this, &AProjectMishkanPlayerController::ReleasedRight);

	InputComponent->BindAction("ZoomIn", IE_Released, this, &AProjectMishkanPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Released, this, &AProjectMishkanPlayerController::ZoomOut);
}

void AProjectMishkanPlayerController::SetBuildMode(EBuildMode mode)
{
	BuildMode = mode;

	// Inform the HUD of the change in Mode
	AMishkanHUD* HUD = Cast<AMishkanHUD>(GetHUD());
	if (HUD) {
		HUD->SetBuildMode(mode);
		HUD->SetInstructionsText(BuildOrder->GetInstructions());
	}
}

// Start placing the selected Vessel
void AProjectMishkanPlayerController::SelectPlaceable(IPlaceable* placeable)
{
	if (BuildMode != EBuildMode::Selection) {
		// Must be in Selection mode to select Vesels
		return;
	}

	Placeable = placeable;
	Placeable->SaveState();
	ChangeToPlacementCamera();

	// Update the camera's location to the Placeable's location
	AMishkanCamera* camera = GetPlacementCamera();
	FVector cameraLoc = camera->GetActorLocation();
	FVector placeableLoc = Placeable->GetLocation();
	cameraLoc.X = placeableLoc.X;
	cameraLoc.Y = placeableLoc.Y;
	camera->SetActorLocation(cameraLoc);

	// Bring the Placeable closer to the screen (relative to the Placement camera)
	placeableLoc.Z = cameraLoc.Z - Placeable->GetSize().Z - PlacementCameraOffset;
	Placeable->SetLocation(placeableLoc);

	SetBuildMode(EBuildMode::Placement);
}

// Lazy loads Main Camera pointer
FORCEINLINE AMishkanCamera* AProjectMishkanPlayerController::GetMainCamera()
{
	if (MainCamera == NULL) {
		MainCamera = GetActorInWorld<AMishkanCamera>(MainCameraName);
	}
	return MainCamera;
}

// Lazy loads Main Camera pointer
FORCEINLINE AMishkanCamera* AProjectMishkanPlayerController::GetPlacementCamera()
{
	if (PlacementCamera == NULL) {
		PlacementCamera = GetActorInWorld<AMishkanCamera>(PlacementCameraName);
	}
	return PlacementCamera;
}

// Looks for the AActor pointer with the given name. Returns NULL if not found
template<typename T>
FORCEINLINE T* AProjectMishkanPlayerController::GetActorInWorld(const FString& Name)
{
	for (TActorIterator<T> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == Name) {
			return *ActorItr;
		}
	}
	return NULL;
}

// Event handlers
void AProjectMishkanPlayerController::SwitchToCharacterMode()
{
	CancelPlacement();		// In case a piece is currently selected
	SetBuildMode(EBuildMode::Character);
	SetViewTarget(PlayerPawn);
	bShowMouseCursor = false;
}

void AProjectMishkanPlayerController::SwitchToSelectionMode()
{
	SetBuildMode(EBuildMode::Selection);
	ChangeToMainCamera();
	bShowMouseCursor = true;
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

void AProjectMishkanPlayerController::PlaceCurrent(IPlaceable* finalPlacement)
{
	ChangeToMainCamera();
	Placeable->PlaceAt(finalPlacement);
	Placeable = NULL;
	SetBuildMode(EBuildMode::Selection);
}

/**
 * Attempt to place the current Placeable at the current spot
 * Will only succeed if we're at the correct step of building and are
 * currently overlapping an equivalent (but hidden) Placeable marker
 */
void AProjectMishkanPlayerController::AttemptPlacement()
{
	if (BuildMode == EBuildMode::Placement) {
		if (BuildOrder->CanBuild(Placeable)) {
			auto overlapped = Placeable->GetWhatsOverlapped();
			for (IPlaceable* other : overlapped) {
				if (Placeable->CanPlaceAt(other)) {
					BuildOrder->Build();
					PlaceCurrent(other);
					return;
				}
			}
			// TODO: Message to user indicating incorrect placement
		}
		else {
			// TODO: Message to user indicating incorrect build step
		}
	}
}

void AProjectMishkanPlayerController::OnCancelButtonClicked()
{
	ChangeToMainCamera();
	CancelPlacement();
}

void AProjectMishkanPlayerController::CancelPlacement()
{
	if (BuildMode == EBuildMode::Placement) {
		Placeable->ResetState();
		Placeable = NULL;
		SetBuildMode(EBuildMode::Selection);
	}
}

// Testing function to show/hide the final placeable positions
void AProjectMishkanPlayerController::ToggleHidePlaceables()
{
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		IPlaceable* placeable = Cast<IPlaceable>(*ActorItr);
		if (placeable != NULL) {
			if (placeable->GetBuildStage() == EVesselBuildStage::Hidden) {
				placeable->ToggleHidden();
			}
		}
	}
}

void AProjectMishkanPlayerController::PressedForward()
{
	PressingForward = true;
}

void AProjectMishkanPlayerController::ReleasedForward()
{
	PressingForward = false;
}

void AProjectMishkanPlayerController::PressedBack()
{
	PressingBack = true;
}

void AProjectMishkanPlayerController::ReleasedBack()
{
	PressingBack = false;
}

void AProjectMishkanPlayerController::PressedLeft()
{
	PressingLeft = true;
}

void AProjectMishkanPlayerController::ReleasedLeft()
{
	PressingLeft = false;
}

void AProjectMishkanPlayerController::PressedRight()
{
	PressingRight = true;
}

void AProjectMishkanPlayerController::ReleasedRight()
{
	PressingRight = false;
}

void AProjectMishkanPlayerController::ZoomIn()
{
	CurrentCamera->ZoomIn();
	ZoomPlaceable();
}

void AProjectMishkanPlayerController::ZoomOut()
{
	CurrentCamera->ZoomOut();
	ZoomPlaceable();
}

// Have the Placeable zoom with the Camera as it zooms
void AProjectMishkanPlayerController::ZoomPlaceable()
{
	if (BuildMode == EBuildMode::Placement) {
		FVector cameraLoc = CurrentCamera->GetActorLocation();
		FVector placeableLoc = Placeable->GetLocation();

		placeableLoc.Z = cameraLoc.Z - Placeable->GetSize().Z - PlacementCameraOffset;
		Placeable->SetLocation(placeableLoc);
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

void AProjectMishkanPlayerController::ChangeToCamera(const FString& Name)
{
	AMishkanCamera* camera = GetActorInWorld<AMishkanCamera>(Name);
	if (camera != NULL) {
		CurrentCamera = camera;
		SetViewTarget(camera);
	}
}