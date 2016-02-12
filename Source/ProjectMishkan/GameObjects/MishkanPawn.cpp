#include "ProjectMishkan.h"
#include "MishkanPawn.h"

const float AMishkanPawn::MISHKAN_MAX_PITCH = 75.f;
const float AMishkanPawn::MOVEMENT_SPEED = 20.f;

AMishkanPawn::AMishkanPawn()
{
	// A Mishkan Pawn is represented by a rectangular prism and a camera, approximately the size of a person (relatively)
	Appearance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppearanceBrush"));
	RootComponent = Appearance;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	Appearance->SetStaticMesh(Cube.Object);
	Appearance->SetRelativeLocation(FVector(-500, -200, 90));
	Appearance->SetWorldScale3D(FVector(0.6f, 0.6f, 1.8f));

	Sight = CreateDefaultSubobject<UCameraComponent>(TEXT("SightCamera"));
	Sight->AttachTo(RootComponent);
	Sight->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	Sight->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AMishkanPawn::MoveForward()
{
	FVector vec = Sight->GetForwardVector();
	vec.Z = 0.0f;
	AddActorLocalOffset(vec * MOVEMENT_SPEED);
}

void AMishkanPawn::MoveBack()
{
	FVector vec = Sight->GetForwardVector();
	vec.Z = 0.0f;
	AddActorLocalOffset(vec * -MOVEMENT_SPEED);
}

void AMishkanPawn::MoveLeft()
{
	FVector vec = Sight->GetRightVector();
	vec.Z = 0.0f;
	AddActorLocalOffset(vec * -MOVEMENT_SPEED);
}

void AMishkanPawn::MoveRight()
{
	FVector vec = Sight->GetRightVector();
	vec.Z = 0.0f;
	AddActorLocalOffset(vec * MOVEMENT_SPEED);
}

void AMishkanPawn::UpdateSight(float deltaYaw, float deltaPitch)
{
	FRotator current = Sight->GetComponentRotation();
	deltaPitch = (FMath::Abs((current.Pitch + deltaPitch)) < MISHKAN_MAX_PITCH) ? deltaPitch : 0;	// Bound the pitch
	Sight->AddRelativeRotation(FRotator(deltaPitch, deltaYaw, 0));
}