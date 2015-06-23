#pragma once

#include "BuildModes.generated.h"

/**
* Data type for building the Mishkan to define the stage of building
*/
UENUM()
enum class EBuildMode : uint8 {
	Selection,		// Select a Vessel to Place
	Placement,		// Vessel selected for Placement
	FirstPerson		// Roam around the Mishkan in First Person mode
};