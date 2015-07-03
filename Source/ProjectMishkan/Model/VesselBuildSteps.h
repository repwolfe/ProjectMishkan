#pragma once

#include "VesselBuildSteps.generated.h"

/**
* Data type to define a unique step in the Mishkan building Process
*/
UENUM()
enum class EVesselBuildStep : uint8 {
	NorthKerashim,
	Shulchan,
	Menorah,
	Undefined
};