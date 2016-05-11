#include "ProjectMishkan.h"
#include "StringConstants.h"

#define LOCTEXT_NAMESPACE "Mishkan"

bool StringConstants::initialized = false;
std::map<EBuildStep, FText> StringConstants::EasyStepInstructions;
std::map<EBuildStep, FText> StringConstants::HardStepInstructions;

StringConstants::StringConstants() {}
StringConstants::StringConstants(StringConstants& Other) {}

void StringConstants::Initialize()
{
	if (initialized == false) {
		SetupEasyStepInstructions();
		SetupHardStepInstructions();
		initialized = true;
	}
}

void StringConstants::SetupEasyStepInstructions()
{
	EasyStepInstructions[EBuildStep::NorthKerashim] = LOCTEXT("BuildInstructions.KerashimNorth.Easy", "There are four Kerashim to be placed on the North side of the Mishkan. Please place them in their correct spot.");
	EasyStepInstructions[EBuildStep::Shulchan] = LOCTEXT("BuildInstructions.Shulchan.Easy", "The shulchan should be built next. It is on the right side of the Mishkan.");
	EasyStepInstructions[EBuildStep::Menorah] = LOCTEXT("BuildInstructions.Menorah.Easy", "The menorah should be built next.");
	EasyStepInstructions[EBuildStep::MizbeachHazahav] = LOCTEXT("BuildInstructions.MizbeachHazahav.Easy", "The Mizbeach HaZahav should be built next on the right side of the Mishkan.");
}

void StringConstants::SetupHardStepInstructions()
{
	HardStepInstructions[EBuildStep::NorthKerashim] = LOCTEXT("BuildInstructions.KerashimNorth.Hard", "And thou shalt build them side by side towards the top.");
	HardStepInstructions[EBuildStep::Shulchan] = LOCTEXT("BuildInstructions.Shulchan.Hard", "And thou shalt build the shulchan.");
	HardStepInstructions[EBuildStep::Menorah] = LOCTEXT("BuildInstructions.Menorah.Hard", "And thou shalt build the menorah.");
	HardStepInstructions[EBuildStep::MizbeachHazahav] = LOCTEXT("BuildInstructions.MizbeachHazahav.Hard", "And thou shalt build the golden mizbeach.");
}


FText StringConstants::GetInstructions(EBuildStep step)
{
	return EasyStepInstructions[step];		// TODO: Make it depend on the difficulty
}

#undef LOCTEXT_NAMESPACE