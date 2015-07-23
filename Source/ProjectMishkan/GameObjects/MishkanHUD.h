#pragma once

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "../Model/BuildModes.h"
#include "MishkanHUD.generated.h"

DECLARE_DELEGATE(FRotationDelegate)

// Container for a Button that appears in the HUD
struct FHUDButton
{
	FCanvasIcon Texture;
	FVector2D Position;
	FVector2D Size;
	FName Name;
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

	void SetBuildMode(EBuildMode mode);
	void SetRotationHandlers(FRotationDelegate RotateLeftF, FRotationDelegate RotateRightF);
	
private:
	void UpdateScale();
	void UpdatePlacementHUD();
	void DrawPlacementHUD();

	// Graphic elements
	float ScaleUI;
	FHUDButton RotateLeft;
	FHUDButton RotateRight;

	FRotationDelegate RotateLeftHandler;
	FRotationDelegate RotateRightHandler;
	EBuildMode CurrentBuildMode;
};