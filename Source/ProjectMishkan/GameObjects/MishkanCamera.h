#pragma once

#include "Camera/CameraActor.h"
#include "MishkanCamera.generated.h"

/**
* Customized Camera in the game
*/
UCLASS()
class PROJECTMISHKAN_API AMishkanCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AMishkanCamera();

	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	void ZoomIn();
	void ZoomOut();
	void ResetHeight();

private:
	// The amount of zoom the camera does each time
	UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0"))
	uint8 ZoomAmount;

	// The Camera's maximum height
	UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0", ClampMax = "3000"))
	uint32 MaxHeight;

	// The Camera's initial height
	UPROPERTY(Category = Mishkan, EditAnywhere)
	uint32 InitialHeight;

	// The Camera's minimum height
	UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1000"))
	uint32 MinHeight;
};