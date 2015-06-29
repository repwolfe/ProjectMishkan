// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "Vessel.h"
#include "../Controllers/ProjectMishkanPlayerController.h"

const uint8 AVessel::RotationAngle = 90;	// Quarter turns

// Sets default values
AVessel::AVessel()
	: VesselType(EVesselType::Undefined), BuildStage(EVesselBuildStage::Hidden), FirstTimeCreating(true)
{
	ThreeDeeModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3D Mesh"));
	ThreeDeeModel->SetMobility(EComponentMobility::Movable);
	RootComponent = ThreeDeeModel;

	PrimaryActorTick.bCanEverTick = false;	// Don't tick every frame
}

// Called after constructor and properties are loaded
void AVessel::PostInitProperties()
{
	SetRotationAmount(FMath::RandRange(0, 3));

	Super::PostInitProperties();
}

// Called after the constructor and properties are loaded
void AVessel::PostRegisterAllComponents()
{
	if (FirstTimeCreating) {
		SetBuildStage(BuildStage);
		FirstTimeCreating = false;
	}

	Super::PostRegisterAllComponents();
}

// Called when the actor is clicked by the mouse
void AVessel::NotifyActorOnClicked()
{
	// Respond to event only if Available
	if (BuildStage == EVesselBuildStage::Available) {
		SelectVessel();
	}
	Super::NotifyActorOnClicked();
}

// Called when the actor is clicked by a finger on a touch device
void AVessel::NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex)
{
	// Respond to event only if Available
	if (BuildStage == EVesselBuildStage::Available) {
		SelectVessel();
	}
	Super::NotifyActorOnInputTouchEnd(FingerIndex);
}

#if WITH_EDITOR
// Called when property is changed in the Unreal Editor
void AVessel::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AVessel, BuildStage)) {
		SetBuildStage(BuildStage);
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

FVector AVessel::GetLocation()
{
	return GetActorLocation();
}

void AVessel::SetLocation(FVector loc)
{
	SetActorLocation(loc);
}

// Saves the current state of the Vessel to be restored at a later time
void AVessel::SaveState()
{
	SavedLocation = GetLocation();
	SavedRotation = CurrentRotation;
}

// Restores the (hopefully) saved state of the Vessel
void AVessel::ResetState()
{
	SetLocation(SavedLocation);
	SetRotationAmount(SavedRotation);
}

void AVessel::RotateRight()
{
	SetRotationAmount((CurrentRotation + 1 == 4) ? 0 : (CurrentRotation + 1));	// Increment or set to 0
}

void AVessel::RotateLeft()
{
	SetRotationAmount((CurrentRotation - 1 < 0) ? 3 : (CurrentRotation - 1));	// Decrement or set to 3
}

// Creates a Box above this Vessel that listens for Available Vessels that enter its perimeter
void AVessel::CreateTriggerBox()
{
	TriggerBox = NewObject<UBoxComponent>(this, TEXT("TriggerBox"));
	TriggerBox->AttachTo(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AVessel::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AVessel::OnEndOverlap);
	TriggerBox->SetRelativeLocation(FVector(0, 0, CameraOffset));
	TriggerBox->RegisterComponent();
}

void AVessel::RemoveTriggerBox()
{
	if (TriggerBox != NULL)
	{
		TriggerBox->UnregisterComponent();
		TriggerBox = NULL;
	}
}

void AVessel::SelectVessel()
{
	// Inform the PlayerController
	auto controller = Cast<AProjectMishkanPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller != NULL) {
		controller->SelectPlaceable(this);
	}
}

// Rotates the Vessel on the Z Axis to the set amount
void AVessel::SetRotationAmount(uint8 Value)
{
	CurrentRotation = Value;
	RootComponent->SetRelativeRotation(FRotator(0, CurrentRotation * RotationAngle, 0));
}

void AVessel::SetBuildStage(EVesselBuildStage Value)
{
	switch (Value) {
		case EVesselBuildStage::Hidden:
			// TODO: Set Visiblity to zero
			CreateTriggerBox();
			break;
		case EVesselBuildStage::Available:		// Do the same for these two Stages
		case EVesselBuildStage::Built:
			// TODO: Make Visible
			RemoveTriggerBox();
			break;
		default:		// Invalid value
			return;
	}
	BuildStage = Value;
}

void AVessel::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("BEGIN OVERLAP"));
}

void AVessel::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("END OVERLAP"));
}