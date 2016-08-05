// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "../Interfaces/IPlaceable.h"
#include "../Model/BuildModes.h"
#include "../Model/BuildOrder.h"
#include "../GameObjects/MishkanCamera.h"
#include "../GameObjects/MishkanPawn.h"
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

	template<typename T>
	T* GetActorInWorld(const FString& Name);

	// Helper functions to lazy load camera pointers
	AMishkanCamera* GetMainCamera();
	AMishkanCamera* GetPlacementCamera();

	// Event Handlers
	void SwitchToCharacterMode();
	void SwitchToSelectionMode();
	void RotateLeft();
	void RotateRight();
	void OnPress();
	void OnRelease();
	void PlaceCurrent(IPlaceable* finalPlacement);
	void AttemptPlacement();
	void OnCancelButtonClicked();
	void CancelPlacement();
	void ToggleHidePlaceables();

	void PressedForward();
	void ReleasedForward();
	void PressedBack();
	void ReleasedBack();
	void PressedLeft();
	void ReleasedLeft();
	void PressedRight();
	void ReleasedRight();

	void ZoomIn();
	void ZoomOut();

	// Helper functions to switch the current camera
	void ChangeToMainCamera();
	void ChangeToPlacementCamera();
	void ChangeToCamera(const FString& Name);

	static const FString PlayerPawnName;

	// Camera variables/constants
	static const FString MainCameraName;
	static const FString PlacementCameraName;
	AMishkanCamera* CurrentCamera;
	AMishkanCamera* MainCamera;
	AMishkanCamera* PlacementCamera;

	const uint16 PlacementCameraOffset = 250;	// Used to calculate how high to place the placeable in Placement Mode
	void ZoomPlaceable();

	EBuildMode BuildMode;
	IPlaceable* Placeable;
	bool MousePressed;

	bool PressingForward, PressingBack, PressingLeft, PressingRight;

	UBuildOrder* BuildOrder;

	AMishkanPawn* PlayerPawn;
};