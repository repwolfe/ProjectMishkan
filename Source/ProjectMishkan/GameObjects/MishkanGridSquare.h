// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MishkanGridSquare.generated.h"

UCLASS()
class PROJECTMISHKAN_API UMishkanGridSquare : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UMishkanGridSquare(const FObjectInitializer& ObjectInitializer);
};
