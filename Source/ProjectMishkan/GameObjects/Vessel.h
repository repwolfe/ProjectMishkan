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

	
	
};
