// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "../Interfaces/IPlaceable.h"
#include "ProjectMishkanPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AProjectMishkanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectMishkanPlayerController(const FObjectInitializer& ObjectInitializer);

	void SelectPlaceable(IPlaceable* placeable);

private:
	virtual void SetupInputComponent() override;

	// Helper functions to lazy load camera pointers
	ACameraActor* GetMainCamera();
	ACameraActor* GetPlacementCamera();
	ACameraActor* GetFirstPersonCamera();
	ACameraActor* GetCamera(const FString& Name);

	// Input Handlers
	void ChangeToMainCamera(float Value);
	void ChangeToPlacementCamera(float Value);
	void ChangeToFirstPersonCamera(float Value);
	void RotateLeft();
	void RotateRight();

	// Helper functions to switch the current camera
	void ChangeToMainCamera();
	void ChangeToPlacementCamera();
	void ChangeToFirstPersonCamera();
	void ChangeToCamera(const FString& Name);

	// Camera variables/constants
	static const FString MainCameraName;
	static const FString PlacementCameraName;
	static const FString FirstPersonCameraName;
	ACameraActor* MainCamera;
	ACameraActor* PlacementCamera;
	ACameraActor* FirstPersonCamera;

	IPlaceable* Placeable;
};