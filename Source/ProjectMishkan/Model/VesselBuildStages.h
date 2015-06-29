#pragma once

#include "VesselBuildStages.generated.h"

/**
* Data type for the different stages a Vessel goes through during building
*/
UENUM()
enum class EVesselBuildStage : uint8 {
	Hidden,		// Reference Vessel in its final position but hidden
	Available,	// Vessel available for Building
	Built		// The Vessel is in its final position
};