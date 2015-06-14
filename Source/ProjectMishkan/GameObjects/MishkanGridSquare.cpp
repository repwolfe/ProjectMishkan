// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "MishkanGridSquare.h"

// Sets default values
UMishkanGridSquare::UMishkanGridSquare(const FObjectInitializer& ObjectInitializer)
	: UStaticMeshComponent(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh.Object) {
		SetStaticMesh(CubeMesh.Object);
	}
}

const TArray<EVesselType>& UMishkanGridSquare::GetContainedVessels() const
{
	return ContainedVessels;
}

void UMishkanGridSquare::SetContainedVessels(TArray<EVesselType>& in)
{
	ContainedVessels = in;
}