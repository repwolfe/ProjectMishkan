// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Model/VesselTypes.h"
#include "MishkanGridSquare.generated.h"

//enum class EVesselType : uint8;		// Forward Declaration

UCLASS()
class PROJECTMISHKAN_API UMishkanGridSquare : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UMishkanGridSquare(const FObjectInitializer& ObjectInitializer);

	const TArray<EVesselType>& GetContainedVessels() const;
	void SetContainedVessels(TArray<EVesselType>& in);

private:
	UPROPERTY(Category = Grid, EditAnywhere)
	TArray<EVesselType> ContainedVessels;
};
