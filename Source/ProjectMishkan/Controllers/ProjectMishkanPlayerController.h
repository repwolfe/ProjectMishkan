// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "../Interfaces/IPlaceable.h"
#include "../Model/BuildModes.h"
#include "../Model/BuildOrder.h"
#include "ProjectMishkanPlayerController.generated.h"

UCLASS()
class AProjectMishkanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void ClientSetHUD_Implementation(TSubclassOf< class AHUD > NewHUDClass) override;
	virtual void PlayerTick(float deltaTime) override;

	void SelectPlaceable(IPlaceable* placeable);

private:
	virtual void SetupInputComponent() override;

	void SetBuildMode(EBuildMode mode);

	// Helper functions to lazy load camera pointers
	ACameraActor* GetMainCamera();
	ACameraActor* GetPlacementCamera();
	ACameraActor* GetFirstPersonCamera();
	ACameraActor* GetCamera(const FString& Name);

	// Event Handlers
	void ChangeToMainCamera(float Value);
	void ChangeToFirstPersonCamera(float Value);
	void RotateLeft();
	void RotateRight();
	void OnPress();
	void OnRelease();
	void PlaceCurrent(IPlaceable* finalPlacement);
	void AttemptPlacement();
	void CancelPlacement();
	void ToggleHidePlaceables();

	// Helper functions to switch the current camera
	void ChangeToMainCamera();
	void ChangeToPlacementCamera();
	void ChangeToFirstPersonCamera();
	void ChangeToCamera(const FString& Name);

	// Camera variables/constants
	static const FString MainCameraName;
	static const FString PlacementCameraName;
	static const FString FirstPersonCameraName;
	ACameraActor* CurrentCamera;
	ACameraActor* MainCamera;
	ACameraActor* PlacementCamera;
	ACameraActor* FirstPersonCamera;

	const uint16 PlacementCameraOffset = 250;	// Used to calculate how high to place the placeable in Placement Mode

	EBuildMode BuildMode;
	IPlaceable* Placeable;
	bool MousePressed;

	UBuildOrder* BuildOrder;
};