#include "ProjectMishkan.h"
#include "../Controllers/ProjectMishkanPlayerController.h"
#include "MishkanHUD.h"

AMishkanHUD::AMishkanHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CurrentBuildMode(EBuildMode::Selection)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ButtonsTextureOb(TEXT("/Game/UI/HUD/Buttons"));
	UTexture2D* ButtonsTexture = ButtonsTextureOb.Object;
	RotateLeft = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 30, 30, 140, 140), TEXT("RotateLeft"));
	RotateRight = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 30, 200, 140, 140), TEXT("RotateRight"));
}

// Custom implementation of Draw, called every frame
void AMishkanHUD::DrawHUD()
{
	Super::DrawHUD();

	UpdateScale();
	switch (CurrentBuildMode) {
		case EBuildMode::Selection:
			break;
		case EBuildMode::Placement:
			UpdatePlacementHUD();
			DrawPlacementHUD();
			break;
		case EBuildMode::FirstPerson:
			break;
	}
}

// Called when a HitBox is clicked
void AMishkanHUD::NotifyHitBoxClick(FName BoxName)
{
	Super::NotifyHitBoxClick(BoxName);

	// Rotation Buttons
	if (BoxName == RotateLeft.Name) {
		RotateLeftHandler.ExecuteIfBound();
	}
	else if (BoxName == RotateRight.Name) {
		RotateRightHandler.ExecuteIfBound();
	}
}

// Set handlers for when rotation buttons are pressed
void AMishkanHUD::SetRotationHandlers(FRotationDelegate RotateLeftF, FRotationDelegate RotateRightF)
{
	if (!RotateLeftHandler.IsBound()) {
		RotateLeftHandler = RotateLeftF;
	}
	if (!RotateRightHandler.IsBound()) {
		RotateRightHandler = RotateRightF;
	}
}

// Ensures everything is an appropriate size regardless of the screen size
FORCEINLINE void AMishkanHUD::UpdateScale()
{
	ScaleUI = Canvas->ClipY / 1080.0f;		// Assuming assets are made for a 1080px tall screen
}

// Makes sure all the things drawn in Placement mode are at their proper position
void AMishkanHUD::UpdatePlacementHUD()
{
	const float Offset = 75.f;

	// Position the Rotation Buttons
	float StartX = Canvas->OrgX + Offset * ScaleUI;
	float StartY = Canvas->ClipY / 2.0f;
	RotateLeft.Position = FVector2D(StartX, StartY - (RotateLeft.Size.Y / 2.0f) * ScaleUI);
	StartX = Canvas->ClipX - Offset * ScaleUI;
	RotateRight.Position = FVector2D(StartX - (RotateRight.Size.X * ScaleUI), StartY - (RotateRight.Size.Y / 2.0f) * ScaleUI);
	
	// Add invisible HitBoxes that detect when the rotation buttons are clicked
	AddHitBox(RotateLeft.Position, RotateLeft.Size, RotateLeft.Name, false);
	AddHitBox(RotateRight.Position, RotateRight.Size, RotateRight.Name, false);
}

// Draws relevant controls/information for Placement mode
FORCEINLINE void AMishkanHUD::DrawPlacementHUD()
{
	// Rotation buttons
	Canvas->DrawIcon(RotateLeft.Texture, RotateLeft.Position.X, RotateLeft.Position.Y, ScaleUI);
	Canvas->DrawIcon(RotateRight.Texture, RotateRight.Position.X, RotateRight.Position.Y, ScaleUI);
}

// Called to inform this what is the current build mode
void AMishkanHUD::SetBuildMode(EBuildMode mode)
{
	CurrentBuildMode = mode;
}