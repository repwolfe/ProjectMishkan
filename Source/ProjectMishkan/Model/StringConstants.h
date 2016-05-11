#pragma once

#include "Internationalization/Text.h"
#include "BuildSteps.h"
#include <map>

/**
 * Static helper class to receive localized text that's useful throughout the game
 */
class PROJECTMISHKAN_API StringConstants {
public:
	static void Initialize();
	static FText GetInstructions(EBuildStep step);
private:
	StringConstants();	// Can't create an instance
	StringConstants(StringConstants& other);		// Don't let people copy this

	static void SetupEasyStepInstructions();
	static void SetupHardStepInstructions();

	static bool initialized;

	static std::map<EBuildStep, FText> EasyStepInstructions;
	static std::map<EBuildStep, FText> HardStepInstructions;
};