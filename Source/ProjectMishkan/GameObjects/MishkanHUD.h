#pragma once

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "../Model/BuildModes.h"
#include "../Model/HUDButtons.h"
#include "InstructionsBox.h"
#include "MishkanHUD.generated.h"

DECLARE_DELEGATE(FHUDButtonDelegate)

// Container for a Button that appears in the HUD
struct FHUDButton
{
	FCanvasIcon Texture;
	FVector2D Position;
	FVector2D Size;
	FName Name;
	FHUDButtonDelegate OnClick;

	FHUDButton(FCanvasIcon Tex, FVector2D Pos, FVector2D Siz, FName Nam)
	{
		Texture = Tex;
		Position = Pos;
		Size = Siz;
		Name = Nam;
	}
	FHUDButton(FCanvasIcon Tex, FName Nam)
		: FHUDButton(Tex, FVector2D::ZeroVector, FVector2D(Tex.UL, Tex.VL), Nam) {}
	FHUDButton() {}
};

// Custom HUD object that draws relevant information / controls
UCLASS()
class AMishkanHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	virtual void DrawHUD() override;
	virtual void NotifyHitBoxClick(FName BoxName) override;

	void SetInstructionsText(FText text);
	void SetBuildMode(EBuildMode mode);
	void SetPlacementHandlers(FHUDButtonDelegate* delegates);
	void OnNewOwningPlayerController(APlayerController* controller);
	
private:
	void UpdateScale();
	void UpdateInstructionsBoxVisibility();
	void UpdateSelectionHUD();
	void DrawSelectionHUD();
	void UpdatePlacementHUD();
	void DrawPlacementHUD();

	// Graphic elements / data
	float ScaleUI;
	FText InstructionsText;

	UFont* SmallFont;
	FColor HUDDark;
	FHUDButton PlacementButtons[EPlacementButton::Size];
	TSubclassOf<UInstructionsBox> InstructionsBoxBP;
	UInstructionsBox* InstructionsBox;
	EBuildMode CurrentBuildMode;
};