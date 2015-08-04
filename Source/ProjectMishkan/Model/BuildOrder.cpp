#include "ProjectMishkan.h"
#include "StringConstants.h"
#include "BuildOrder.h"

const std::vector<EBuildStep> UBuildOrder::BuildSteps = {
	EBuildStep::NorthKerashim,
	EBuildStep::Shulchan,
	//EBuildStep::Menorah,
	EBuildStep::MizbeachHazahav
};
const uint8 UBuildOrder::NumSteps = BuildSteps.size();

const std::map<EBuildStep, uint8> UBuildOrder::VesselsPerStep = {
	{EBuildStep::NorthKerashim, 4},
	{EBuildStep::Shulchan, 1},
	//{EBuildStep::Menorah, 1},
	{EBuildStep::MizbeachHazahav, 1}
};

UBuildOrder::UBuildOrder()
	: CurrentStep(0), VesselsBuildThisStep(0)
{
}

// Check to see if the request to build @param step is valid
bool UBuildOrder::CanBuild(IPlaceable* placeable) const
{
	// Check to see if still building
	if (CurrentStep >= 0 && CurrentStep < BuildSteps.size()) {
		return placeable->GetBuildStep() == BuildSteps[CurrentStep];
	}
	return false;
}

// Proceed to the next step
void UBuildOrder::Build()
{
	if (++VesselsBuildThisStep == VesselsPerStep.at(Current())) {
		// Built enough this step
		++CurrentStep;
		VesselsBuildThisStep = 0;
	}
}

FText UBuildOrder::GetInstructions() const
{
	return StringConstants::GetInstructions(Current());
}

// Returns the current build step
FORCEINLINE EBuildStep UBuildOrder::Current() const
{
	if (CurrentStep >= 0 && CurrentStep < BuildSteps.size()) {
		return BuildSteps[CurrentStep];
	}
	return EBuildStep::Undefined;
}