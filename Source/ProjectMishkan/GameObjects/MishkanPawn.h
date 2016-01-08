#pragma once

#include "GameFramework/Pawn.h"
#include "MishkanPawn.generated.h"

/**
* Controllable Character in the game
*/
UCLASS()
class PROJECTMISHKAN_API AMishkanPawn : public APawn
{
	GENERATED_BODY()

public:
	AMishkanPawn();

	void MoveForward();
	void MoveBack();
	void MoveLeft();
	void MoveRight();
	void UpdateSight(float deltaYaw, float deltaPitch);

private:
	UCameraComponent* Sight;				// The Character's Sight
	UStaticMeshComponent* Appearance;	// A Rectangular Prism representing the Pawn's appearance
};