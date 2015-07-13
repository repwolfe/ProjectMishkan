#pragma once

#include "BuildSteps.generated.h"

/**
* Data type to define a unique step in the Mishkan building Process
*/
UENUM()
enum class EBuildStep : uint8 {
	NorthKerashim,		// North Wooden boards
	Shulchan,			// Table
	Menorah,			// Candelabra
	MizbeachHazahav,	// Golden Altar
	Undefined
};

/* Potential build steps
Adanim,					// Silver sockets
Amudim,					// Gold-plated beams
AronHakodesh,			// Ark
Berichim,				// Bars (for the Kerashim)
Kior,					// Water basin
Kerashim,				// Wooden boards
MasachPesachOhelMoed,	// Entrance curtains
MeitareiOhelMoed,		// What is this?
Menorah,				// The Golden Candelabra
Mishkan,				// Tabernacle spread
MizbeachHanechoshes,	// Copper Altar
MizbeachHazahav,		// Golden Altar
Paroches,				// Curtain / Veil
Shulchan,				// Table
YeriosIzim,				// Curtains of Goats' hair
Undefined
*/