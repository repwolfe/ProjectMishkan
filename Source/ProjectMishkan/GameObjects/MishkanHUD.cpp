#include "ProjectMishkan.h"
#include "../Controllers/ProjectMishkanPlayerController.h"
#include "MishkanHUD.h"

AMishkanHUD::AMishkanHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CurrentBuildMode(EBuildMode::Selection)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ButtonsTextureOb(TEXT("/Game/UI/HUD/Buttons"));
	UTexture2D* ButtonsTexture = ButtonsTextureOb.Object;
	PlacementButtons[EPlacementButton::RotateLeft] = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 50, 50, 250, 250), TEXT("RotateLeft"));
	PlacementButtons[EPlacementButton::RotateRight] = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 50, 350, 250, 250), TEXT("RotateRight"));
	PlacementButtons[EPlacementButton::Okay] = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 50, 650, 180, 180), TEXT("Okay"));
	PlacementButtons[EPlacementButton::Cancel] = FHUDButton(UCanvas::MakeIcon(ButtonsTexture, 50, 880, 180, 180), TEXT("Cancel"));
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

	for (uint8 i = 0; i < EPlacementButton::Size; ++i) {
		if (BoxName == PlacementButtons[i].Name) {
			PlacementButtons[i].OnClick.ExecuteIfBound();
			return;		// No point continuing, hit box names are unique
		}
	}
}

// Set handlers for when rotation buttons are pressed
void AMishkanHUD::SetPlacementHandlers(FHUDButtonDelegate* delegates)
{
	for (uint8 i = 0; i < EPlacementButton::Size; ++i) {
		if (!PlacementButtons[i].OnClick.IsBound()) {
			PlacementButtons[i].OnClick = delegates[i];
		}
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
	FHUDButton* button;
	float StartX, StartY;

	// Left Rotation Button
	button = &PlacementButtons[EPlacementButton::RotateLeft];
	StartX = Canvas->OrgX + Offset * ScaleUI;
	StartY = Canvas->SizeY / 2.0f;
	button->Position = FVector2D(StartX, StartY - (button->Size.Y / 2.0f) * ScaleUI);

	// Right Rotation Button (same Y)
	button = &PlacementButtons[EPlacementButton::RotateRight];
	StartX = Canvas->SizeX - Offset * ScaleUI;
	button->Position = FVector2D(StartX - (button->Size.X * ScaleUI), StartY - (button->Size.Y / 2.0f) * ScaleUI);
	
	// Okay button
	button = &PlacementButtons[EPlacementButton::Okay];
	StartX = Canvas->SizeX / 2.0f - 1.5f * Offset * ScaleUI;
	StartY = Canvas->SizeY - Offset * ScaleUI;
	button->Position = FVector2D(StartX - (button->Size.X / 2.0f) * ScaleUI, StartY - button->Size.Y * ScaleUI);

	// Cancel button (same X)
	button = &PlacementButtons[EPlacementButton::Cancel];
	StartX = Canvas->SizeX / 2.0f + 1.5f * Offset * ScaleUI;
	button->Position = FVector2D(StartX + (button->Size.X / 2.0f) * ScaleUI, StartY - button->Size.Y * ScaleUI);

	// Add invisible HitBoxes that detect when the buttons are clicked
	for (uint8 i = 0; i < EPlacementButton::Size; ++i) {
		button = &PlacementButtons[i];
		AddHitBox(button->Position, button->Size * ScaleUI, button->Name, false);
	}
}

// Draws relevant controls/information for Placement mode
void AMishkanHUD::DrawPlacementHUD()
{
	FHUDButton* button;
	for (uint8 i = 0; i < EPlacementButton::Size; ++i) {
		button = &PlacementButtons[i];
		Canvas->DrawIcon(button->Texture, button->Position.X, button->Position.Y, ScaleUI);
	}
}

// Called to inform this what is the current build mode
void AMishkanHUD::SetBuildMode(EBuildMode mode)
{
	CurrentBuildMode = mode;
}