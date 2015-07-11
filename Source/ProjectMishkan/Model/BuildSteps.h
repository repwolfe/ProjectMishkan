#pragma once

#include "BuildSteps.generated.h"

/**
* Data type to define a unique step in the Mishkan building Process
*/
UENUM()
enum class EBuildStep : uint8 {
	NorthKerashim,
	Shulchan,
	Menorah,
	MizbeachHazahav,
	Undefined
};