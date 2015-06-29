// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Model/VesselTypes.h"
#include "../Model/VesselBuildStages.h"
#include "../Interfaces/IPlaceable.h"
#include "Vessel.generated.h"

/**
 * 3D object that is part of the Mishkan
 */
UCLASS()
class PROJECTMISHKAN_API AVessel : public AActor, public IPlaceable
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AVessel();

	// Called after constructor and properties are loaded
	virtual void PostInitProperties() override;

	// Called after the constructor and properties are loaded
	virtual void PostRegisterAllComponents() override;

	// Called when the actor is clicked by the mouse
	virtual void NotifyActorOnClicked() override;

	// Called when the actor is clicked by a finger on a touch device
	virtual void NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex) override;

	// Called when property is changed in the Unreal Editor
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual FVector GetLocation() override;
	virtual void SetLocation(FVector loc) override;
	virtual void SaveState() override;
	virtual void ResetState() override;
	virtual void RotateRight() override;
	virtual void RotateLeft() override;

private:
	void CreateTriggerBox();
	void RemoveTriggerBox();
	void SelectVessel();
	void SetRotationAmount(uint8 Value);
	void SetBuildStage(EVesselBuildStage Value);

	UFUNCTION()
	void OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	// The Static Mesh that stores the 3D Model
	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ThreeDeeModel;

	// Trigger Box to detect overlaps
	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox;

	// How many degrees a single rotation does
	static const uint8 RotationAngle;

	UPROPERTY(Category = Mishkan, EditAnywhere)
	EVesselType VesselType;

	UPROPERTY(Category = Mishkan, EditAnywhere)
	EVesselBuildStage BuildStage;

	// TODO: Remove this??
	// The final location of this Vessel in the Mishkan
	//UPROPERTY(Category = Mishkan, EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	//FIntPoint GridLocation;

	// The final rotation amounts of this Vessel in the Mishkan (how many quarter turns)
	UPROPERTY(Category = Mishkan, EditAnywhere)
	TArray<uint8> FinalRotations;

	// Place the Vessel in its final location or not
	//UPROPERTY(Category = Mishkan, EditAnywhere)
	//bool PlaceOnGrid;

	// The Vessel's current rotation amount (how many quarter turns)
	UPROPERTY(Category = Mishkan, VisibleAnywhere, meta = (ClampMin = "0", ClampMax = "3"))
	uint8 CurrentRotation;	

	bool FirstTimeCreating;

	// Saved State variables
	FVector SavedLocation;
	uint8 SavedRotation;
};
