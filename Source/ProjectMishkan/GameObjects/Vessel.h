// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vessel.generated.h"

UCLASS()
class PROJECTMISHKAN_API AVessel : public AActor
{
	GENERATED_BODY()
	
	// The Static Mesh that stores the 3D Model
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ThreeDeeModel;

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
	static const uint8 RotationAngle;

	// The final location of this Vessel in the Mishkan
	UPROPERTY(Category = Mishkan, EditAnywhere)
	FVector2D GridLocation;

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
