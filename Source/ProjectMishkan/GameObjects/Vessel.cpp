// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "Vessel.h"

const uint8 AVessel::RotationAngle = 90;	// Quarter turns

// Sets default values
AVessel::AVessel()
	: GridLocation(0, 0), GridRotation(0), PlaceOnGrid(false), CurrentRotation(FMath::RandRange(0, 3))
{
	ThreeDeeModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3D Mesh"));
	RootComponent = ThreeDeeModel;

	// Rotate the mesh the correct amount
	RootComponent->RelativeRotation.Yaw = CurrentRotation * RotationAngle;

	PrimaryActorTick.bCanEverTick = false;	// Don't tick every frame

}

// Called when the game starts or when spawned
void AVessel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVessel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

#if WITH_EDITOR
// Called when property is changed in the Unreal Editor
void AVessel::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	float rotationAmount = 0;
	if (PlaceOnGrid) {		// Set the Vessel to be in its final location in the grid
		rotationAmount = GridRotation * RotationAngle;
	}
	else {		// Set the Vessel to be back in its current location
		rotationAmount = CurrentRotation * RotationAngle;
	}
	RootComponent->RelativeRotation.Yaw = rotationAmount;

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
