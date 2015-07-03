#pragma once

#include "VesselBuildSteps.h"
#include "BuildOrder.generated.h"

/**
 * Manages the Current Build Step
 */
UCLASS()
class PROJECTMISHKAN_API UBuildOrder : public UObject {
	GENERATED_BODY()

public:
	UBuildOrder();
	EVesselBuildStep Current();

private:
	void Next();

	TArray<EVesselBuildStep> BuildSteps;
	uint8 CurrentStep;
};