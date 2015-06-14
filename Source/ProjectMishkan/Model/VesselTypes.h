#pragma once

#include "VesselTypes.generated.h"

/**
 * Data type to define each unique Vessel
 */
UENUM()
enum class EVesselType : uint8 {
	// Try to keep this alphabetical
	Aron,
	Menorah,
	MizbeachHanechoshes,
	MizbeachHazahav,
	Shulchan,
	Undefined
};