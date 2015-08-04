#include "ProjectMishkan.h"
#include "StringConstants.h"

#define LOCTEXT_NAMESPACE "Mishkan"

FText StringConstants::GetInstructions(EBuildStep step)
{
	return LOCTEXT("BuildInstructions.KerashimNorth", "You must build the north Kerashim!");
}

#undef LOCTEXT_NAMESPACE