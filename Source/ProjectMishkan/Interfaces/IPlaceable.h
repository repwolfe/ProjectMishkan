#pragma once

class PROJECTMISHKAN_API IPlaceable {
public:
	virtual FVector GetLocation() = 0;
	virtual void SetLocation(FVector loc) = 0;
	virtual void RotateRight() = 0;
	virtual void RotateLeft() = 0;
};