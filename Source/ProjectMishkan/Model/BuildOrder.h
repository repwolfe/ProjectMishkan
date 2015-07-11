#pragma once

#include <vector>
#include <map>
#include "../Interfaces/IPlaceable.h"
#include "BuildOrder.generated.h"

/**
 * Manages the Current Build Step
 */
UCLASS()
class PROJECTMISHKAN_API UBuildOrder : public UObject {
	GENERATED_BODY()

public:
	UBuildOrder();
	bool CanBuild(IPlaceable* placeable);
	void Build();

private:
	EBuildStep Current();

	static const std::vector<EBuildStep> BuildSteps;
	static const uint8 NumSteps;
	static const std::map<EBuildStep, uint8> VesselsPerStep;

	uint8 CurrentStep;
	uint8 VesselsBuildThisStep;
};