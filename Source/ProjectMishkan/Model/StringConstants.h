#pragma once

#include "Internationalization/Text.h"
#include "BuildSteps.h"
#include <map>

class PROJECTMISHKAN_API StringConstants {
public:
	static StringConstants* Instance();
	FText GetInstructions(EBuildStep step);
private:
	StringConstants();		// Singleton
	StringConstants(StringConstants& other);		// Don't let people call this

	void SetupEasyStepInstructions();
	void SetupHardStepInstructions();

	static StringConstants* InstancePointer;

	std::map<EBuildStep, FText> EasyStepInstructions;
	std::map<EBuildStep, FText> HardStepInstructions;
};