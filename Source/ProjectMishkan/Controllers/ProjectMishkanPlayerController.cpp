// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ProjectMishkan.h"
#include "../GameObjects/MishkanHUD.h"
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

	BuildOrder = NewObject<UBuildOrder>(this, TEXT("BuildOrder"));
}

// Called when the HUD is changed
void AProjectMishkanPlayerController::ClientSetHUD_Implementation(TSubclassOf< class AHUD > NewHUDClass)
{
	Super::ClientSetHUD_Implementation(NewHUDClass);

	// Assume it's MishkanHUD
	AMishkanHUD* HUD = Cast<AMishkanHUD>(GetHUD());
	if (HUD) {
		FHUDButtonDelegate handlers[EPlacementButton::Size];
		handlers[EPlacementButton::RotateLeft].BindUObject(this, &AProjectMishkanPlayerController::RotateLeft);
		handlers[EPlacementButton::RotateRight].BindUObject(this, &AProjectMishkanPlayerController::RotateRight);
		handlers[EPlacementButton::Okay].BindUObject(this, &AProjectMishkanPlayerController::AttemptPlacement);
		handlers[EPlacementButton::Cancel].BindUObject(this, &AProjectMishkanPlayerController::CancelPlacement);
		HUD->SetPlacementHandlers(handlers);
	}
}

// Called every Frame
void AProjectMishkanPlayerController::PlayerTick(float deltaTime)
{
	// If in placement mode, check if mouse pressed and dragged, move camera/placeable
	if (BuildMode == EBuildMode::Placement && MousePressed) {
		const uint8 SCALE_VALUE = 20;
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
	InputComponent->BindAction("SwitchToFirstPersonCamera", IE_Released, this, &AProjectMishkanPlayerController::ChangeToFirstPersonCamera);
	InputComponent->BindAction("RotateLeft", IE_Released, this, &AProjectMishkanPlayerController::RotateLeft);
	InputComponent->BindAction("RotateRight", IE_Released, this, &AProjectMishkanPlayerController::RotateRight);
	InputComponent->BindAction("OnPress", IE_Pressed, this, &AProjectMishkanPlayerController::OnPress);
	InputComponent->BindAction("OnRelease", IE_Released, this, &AProjectMishkanPlayerController::OnRelease);
	InputComponent->BindAction("AttemptPlacement", IE_Released, this, &AProjectMishkanPlayerController::AttemptPlacement);
	InputComponent->BindAction("CancelPlacement", IE_Released, this, &AProjectMishkanPlayerController::CancelPlacement);
}

void AProjectMishkanPlayerController::SetBuildMode(EBuildMode mode)
{
	BuildMode = mode;

	// Inform the HUD of the change in Mode
	AMishkanHUD* HUD = Cast<AMishkanHUD>(GetHUD());
	if (HUD) {
		HUD->SetBuildMode(mode);
	}
}

// Start placing the selected Vessel
void AProjectMishkanPlayerController::SelectPlaceable(IPlaceable* placeable)
{
	if (BuildMode == EBuildMode::Placement) {
		// Already in placement mode, ignore selections
		return;
	}

	Placeable = placeable;
	Placeable->SaveState();
	ChangeToPlacementCamera();

	// Update the camera's location to the Placeable's location
	ACameraActor* camera = GetPlacementCamera();
	FVector cameraLoc = camera->GetActorLocation();
	FVector placeableLoc = Placeable->GetLocation();
	cameraLoc.X = placeableLoc.X;
	cameraLoc.Y = placeableLoc.Y;
	cameraLoc.Z = IPlaceable::CameraOffset * 2;		// Be twice as high as the Placeable is
	camera->SetActorLocation(cameraLoc);

	// Bring the Placeable closer to the screen (relative to the Placement camera)
	placeableLoc.Z = IPlaceable::CameraOffset;
	Placeable->SetLocation(placeableLoc);

	SetBuildMode(EBuildMode::Placement);
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
	SetBuildMode(EBuildMode::Selection);
	ChangeToMainCamera();
}

void AProjectMishkanPlayerController::ChangeToFirstPersonCamera(float Value)
{
	SetBuildMode(EBuildMode::FirstPerson);
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

void AProjectMishkanPlayerController::CancelPlacement()
{
	ChangeToMainCamera();
	if (BuildMode == EBuildMode::Placement) {
		Placeable->ResetState();
		Placeable = NULL;
		SetBuildMode(EBuildMode::Selection);
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