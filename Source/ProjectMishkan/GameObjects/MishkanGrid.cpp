// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "MishkanGrid.h"
#include "MishkanGridSquare.h"
#include "../Model/MishkanGridSave.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMishkanGrid::AMishkanGrid()
	: GridSize(2, 2), SquareSize(20), SaveGrid(false), FirstTimeCreating(true)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh.Object) {
		GridCubeMesh = CubeMesh.Object;
	}
	ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Engine/EngineMaterials/CubeMaterial.CubeMaterial'"));
	if (Material.Object) {
		GridMaterial = Material.Object;
	}

	PrimaryActorTick.bCanEverTick = false;
}

// Called after the constructor and properties are loaded
void AMishkanGrid::PostRegisterAllComponents()
{
	if (FirstTimeCreating) {
		PreviousGridSize = GridSize;
		FirstTimeCreating = false;
		CreateStaticMesh();
		CreateGridSquares();
	}
	Super::PostRegisterAllComponents();
}

// Called when the game starts or when spawned
void AMishkanGrid::BeginPlay()
{
	Super::BeginPlay();
}

// Creates the Grid's own Static Mesh
void AMishkanGrid::CreateStaticMesh()
{
	if (GridMesh != NULL) {
		GridMesh->DestroyComponent();
	}
	GridMesh = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("GridMesh"));
	GridMesh->SetStaticMesh(GridCubeMesh);	// TODO: Check for null?
	GridMesh->SetMaterial(0, GridMaterial);
	GridMesh->SetRelativeLocation(FVector(0, 0, 300));		// TODO: Get its stored location
	GridMesh->SetRelativeScale3D(FVector(GridSize.X, GridSize.Y, 0.01f));
	GridMesh->RegisterComponent();
	RootComponent = GridMesh;
}

// Creates the GridSquares and positions depending on the GridSize
void AMishkanGrid::CreateGridSquares()
{
	const float parentSize = 100.0f;	// Relative size that is equal to parent (ie: 100%)
	const float gridSquareSizeX = parentSize / (float) GridSize.X;
	const float gridSquareSizeY = parentSize / (float) GridSize.Y;
	const float centerOffsetX = -gridSquareSizeX * 0.5f;	// Offset from top left corner to middle of square
	const float centerOffsetY = gridSquareSizeY * 0.5f;

	const float topLeftY = -parentSize * 0.5f;	// Start placing grid pieces at the top left corner of the grid
	float currentX = parentSize * 0.5f;
	float currentY = topLeftY;
	
	const FVector squareScale(1 / (float) GridSize.X, 1 / (float) GridSize.Y, 1.0f);
	uint8 i = 0;
	
	for (uint8 width = 0; width < GridSize.X; ++width) {
		for (uint8 height = 0; height < GridSize.Y; ++height) {
			const FVector squareLocation = FVector(currentX + centerOffsetX, currentY + centerOffsetY, 2.0f);
			UMishkanGridSquare* newSquare = ConstructObject<UMishkanGridSquare>(UMishkanGridSquare::StaticClass(), this, *FString::Printf(TEXT("GridSquare%d"), i++));
			newSquare->RegisterComponent();	// TODO: Check for null?
			newSquare->SetRelativeLocation(squareLocation);
			newSquare->SetRelativeScale3D(squareScale);
			newSquare->AttachTo(RootComponent);
			currentY += gridSquareSizeY;
		}
		currentY = topLeftY;
		currentX -= gridSquareSizeX;
	}
}

#if WITH_EDITOR
// Called when property is changed in the Unreal Editor
void AMishkanGrid::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	if (SaveGrid == true) {		// If they checked the Save Grid checkbox, save to a file
		
		SaveGrid = false;
	}
	else if (PreviousGridSize != GridSize) {		// If they changed either the X or Y of the Grid Size
		// TODO: Don't delete the old grid, simply update it
		CreateStaticMesh();
		CreateGridSquares();
		PreviousGridSize = GridSize;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

