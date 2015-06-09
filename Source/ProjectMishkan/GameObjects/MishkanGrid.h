// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MishkanGrid.generated.h"

UCLASS()
class PROJECTMISHKAN_API AMishkanGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMishkanGrid();

	// Called after the constructor and properties are loaded
	virtual void PostRegisterAllComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when property is changed in the Unreal Editor
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	// Creates the Grid's own static mesh
	void CreateStaticMesh();

	// Creates and positions the GridSquares depending on the GridSize
	void CreateGridSquares();

	// The Static Mesh to display the grid
	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GridMesh;

	// The size of a Square in the grid
	UPROPERTY(Category = GridData, EditAnywhere, meta = (ClampMin = "1", UIMin = "1"))
	uint8 SquareSize;

	// The size of the grid in square units
	UPROPERTY(Category = GridData, EditAnywhere, meta = (ClampMin = "1", ClampMax = "200", UIMin = "1", UIMax = "200"))
	FIntPoint GridSize;

	// Display variables
	UStaticMesh* GridCubeMesh;
	UMaterial* GridMaterial;

	bool FirstTimeCreating;

	// Used to see if GridSize changes
	FIntPoint PreviousGridSize;
};
