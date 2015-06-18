// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "Vessel.h"
#include "../Controllers/ProjectMishkanPlayerController.h"

const uint8 AVessel::RotationAngle = 90;	// Quarter turns

// Sets default values
AVessel::AVessel()
	: VesselType(EVesselType::Undefined), GridLocation(0, 0), GridRotation(0), PlaceOnGrid(false)
{
	ThreeDeeModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3D Mesh"));
	ThreeDeeModel->SetMobility(EComponentMobility::Movable);
	RootComponent = ThreeDeeModel;

	PrimaryActorTick.bCanEverTick = false;	// Don't tick every frame
}

// Called after constructor and properties are loaded
void AVessel::PostInitProperties()
{
	SetRotationAmount(FMath::RandRange(0, 3));

	Super::PostInitProperties();
}

// Called when the actor is clicked by the mouse
void AVessel::NotifyActorOnClicked()
{
	SelectVessel();
	Super::NotifyActorOnClicked();
}

// Called when the actor is clicked by a finger on a touch device
void AVessel::NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex)
{
	SelectVessel();
	Super::NotifyActorOnInputTouchEnd(FingerIndex);
}

#if WITH_EDITOR
// Called when property is changed in the Unreal Editor
void AVessel::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PlaceOnGrid) {		// Set the Vessel to be in its final location in the grid
		RootComponent->RelativeRotation.Yaw = GridRotation * RotationAngle;
	}
	else {		// Set the Vessel to be back in its current location
		RootComponent->RelativeRotation.Yaw = CurrentRotation * RotationAngle;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AVessel::RotateRight()
{
	SetRotationAmount((CurrentRotation + 1 == 4) ? 0 : (CurrentRotation + 1));	// Increment or set to 0
}

void AVessel::RotateLeft()
{
	SetRotationAmount((CurrentRotation - 1 < 0) ? 3 : (CurrentRotation - 1));	// Decrement or set to 3
}

void AVessel::SelectVessel()
{
	// Inform the PlayerController
	auto controller = Cast<AProjectMishkanPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller != NULL) {
		controller->SelectPlaceable(this);
	}
}

// Rotates the Vessel on the Z Axis to the set amount
void AVessel::SetRotationAmount(uint8 Value)
{
	CurrentRotation = Value;
	RootComponent->SetRelativeRotation(FRotator(0, CurrentRotation * RotationAngle, 0));
}