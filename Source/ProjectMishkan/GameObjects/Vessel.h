// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Model/VesselTypes.h"
#include "Vessel.generated.h"

/**
 * 3D object that is part of the Mishkan
 */
UCLASS()
class PROJECTMISHKAN_API AVessel : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AVessel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called when property is changed in the Unreal Editor
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	// The Static Mesh that stores the 3D Model
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ThreeDeeModel;

	// How many degrees a single rotation does
	static const uint8 RotationAngle;

	UPROPERTY(Category = Mishkan, EditAnywhere)
	EVesselType VesselType;

	// TODO: Remove this??
	// The final location of this Vessel in the Mishkan
	UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	FIntPoint GridLocation;

	// The final rotation amount of this Vessel in the Mishkan (how many quarter turns)
	UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
	uint8 GridRotation;

	// Place the Vessel in its final location or not
	UPROPERTY(Category = Mishkan, EditAnywhere)
	bool PlaceOnGrid;

	// The Vessel's current rotation amount (how many quarter turns)
	UPROPERTY(Category = Mishkan, VisibleAnywhere, meta = (ClampMin = "0", ClampMax = "3"))
	uint8 CurrentRotation;
	
};
