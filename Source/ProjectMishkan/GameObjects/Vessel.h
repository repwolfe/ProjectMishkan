// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vessel.generated.h"

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

private:
	// The final location of this Vessel in the Mishkan
	UPROPERTY(Category = Mishkan, EditAnywhere)
	FVector2D GridLocation;

	// The final rotation amount of this Vessel in the Mishkan (values 0 - 3)
	UPROPERTY(Category = Mishkan, EditAnywhere)
	float GridRotation;

	// Place the Vessel in it's final location or not
	UPROPERTY(Category = Mishkan, EditAnywhere)
	bool PlaceOnGrid;

	// The Vessel's current rotation amount
	UPROPERTY(Category = Mishkan, VisibleAnywhere)
	float currentRotation;
	
};
