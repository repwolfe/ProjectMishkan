#pragma once

/**
* Data type for Buttons that appear in Placement Mode
*/
struct EPlacementButtonsWrapper {		// Allows us to use enum as array index
	enum EPlacementButton {
		RotateLeft,
		RotateRight,
		Okay,
		Cancel,
		Size		// Marker for how many elements in the enum, keep last
	};
};
typedef EPlacementButtonsWrapper::EPlacementButton EPlacementButton;