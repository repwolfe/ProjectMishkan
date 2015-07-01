#pragma once

#include <list>
#include "IPlaceable.generated.h"

// Boilerplate code to allow for an Unreal Interface
UINTERFACE()
class PROJECTMISHKAN_API UPlaceable : public UInterface {
	GENERATED_UINTERFACE_BODY()
};

// The interface of something that can be placed in the Mishkan
class PROJECTMISHKAN_API IPlaceable {
	GENERATED_IINTERFACE_BODY()

public:
	virtual FVector GetLocation() = 0;
	virtual const std::list<IPlaceable*>& GetWhatsOverlapped() const = 0;
	virtual void SetLocation(FVector loc) = 0;
	virtual void SaveState() = 0;
	virtual void ResetState() = 0;
	virtual void RotateRight() = 0;
	virtual void RotateLeft() = 0;
	virtual bool CanPlaceAt(IPlaceable* finalPlacement) = 0;
	virtual void PlaceAt(IPlaceable* finalPlacement) = 0;

	static const uint8 CameraOffset;	// How far up to move the Placeable when in Placement mode
};