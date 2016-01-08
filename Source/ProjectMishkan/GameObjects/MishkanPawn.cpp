#include "ProjectMishkan.h"
#include "MishkanPawn.h"

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
	Sight->SetRelativeLocation(FVector(100.0f, 0.0f, 25.0f));
	Sight->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AMishkanPawn::MoveForward()
{
	//AddActorLocalOffset(GetActorForwardVector() * 5.0f);
}

void AMishkanPawn::MoveBack()
{
	//AddActorLocalOffset(GetActorForwardVector() * -5.0f);
}

void AMishkanPawn::MoveLeft()
{

}

void AMishkanPawn::MoveRight()
{
}

void AMishkanPawn::UpdateSight(float deltaYaw, float deltaPitch)
{
	//Appearance->AddRelativeRotation(FRotator(0, deltaYaw, 0));
	Sight->AddRelativeRotation(FRotator(deltaPitch, deltaYaw, 0));
}