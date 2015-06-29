#pragma once

class PROJECTMISHKAN_API IPlaceable {
public:
	virtual FVector GetLocation() = 0;
	virtual void SetLocation(FVector loc) = 0;
	virtual void SaveState() = 0;
	virtual void ResetState() = 0;
	virtual void RotateRight() = 0;
	virtual void RotateLeft() = 0;

	static const uint8 CameraOffset;	// How far up to move the Placeable when in Placement mode
};