#include "ProjectMishkan.h"
#include "BuildOrder.h"

UBuildOrder::UBuildOrder()
{

}

// Returns the current build step
EVesselBuildStep UBuildOrder::Current()
{
	if (CurrentStep >= 0 && CurrentStep < BuildSteps.Num()) {
		return BuildSteps[CurrentStep];
	}
	return EVesselBuildStep::Undefined;
}

// Proceeds to the next build step
void UBuildOrder::Next()
{
	++CurrentStep;
}