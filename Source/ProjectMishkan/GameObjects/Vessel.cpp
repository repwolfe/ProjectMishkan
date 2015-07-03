// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectMishkan.h"
#include "Vessel.h"
#include "../Controllers/ProjectMishkanPlayerController.h"

const uint8 AVessel::RotationAngle = 90;	// Quarter turns
const uint8 AVessel::BoundingBoxBufferScale = 3;

// Sets default values
AVessel::AVessel()
	: VesselType(EVesselType::Undefined), BuildStage(EVesselBuildStage::Hidden), BuildStep(EVesselBuildStep::Undefined), FirstTimeCreating(true)
{
	ThreeDeeModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3D Mesh"));
	ThreeDeeModel->SetMobility(EComponentMobility::Movable);
	RootComponent = ThreeDeeModel;

	PrimaryActorTick.bCanEverTick = false;	// Don't tick every frame
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

// Called when Actor is removed from the level
void AVessel::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	RemoveTriggerBox();
	Super::EndPlay(EndPlayReason);
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

/**
 * @returns true if this Vessel can be placed where finalPlacement is located by checking if
 * a) finalPlacement is also a Vessel
 * b) Both Vessels have the same VesselType
 * c) this is rotated a valid amount
 */
bool AVessel::CanPlaceAt(IPlaceable* finalPlacement)
{
	AVessel* finalVessel = Cast<AVessel>(finalPlacement);
	if (finalVessel && VesselType == finalVessel->VesselType) {
		for (uint8 validRotation : finalVessel->FinalRotations) {
			if (CurrentRotation == validRotation) {
				return true;
			}
		}
	}
	return false;
}

/**
 * Make this Vessel disappear and the final Vessel marker that until
 * now is hidden, start building it
 */
void AVessel::PlaceAt(IPlaceable* finalPlacement)
{
	// TODO: Start building the Vessel
	AVessel* vessel = Cast<AVessel>(finalPlacement);
	vessel->SetBuildStage(EVesselBuildStage::Built);
	Destroy();
}

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

FORCEINLINE const std::list<IPlaceable*>& AVessel::GetWhatsOverlapped() const
{
	return VesselsOverlapped;
}

/*
 * Creates a Box above this Vessel that listens for Available Vessels that enter its perimeter
 * Generates an event which will subsequently inform the Available Vessel that is overlapping this
 */
void AVessel::CreateTriggerBox()
{
	auto BoundingBox = ThreeDeeModel->Bounds.BoxExtent;
	BoundingBox *= BoundingBoxBufferScale;

	TriggerBox = NewObject<UBoxComponent>(this, TEXT("TriggerBox"));
	TriggerBox->AttachTo(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AVessel::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AVessel::OnEndOverlap);
	TriggerBox->SetRelativeLocation(FVector(0, 0, CameraOffset));
	TriggerBox->SetBoxExtent(BoundingBox);
	TriggerBox->RegisterComponent();
}

void AVessel::RemoveTriggerBox()
{
	if (TriggerBox != NULL)
	{
		TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &AVessel::OnBeginOverlap);
		TriggerBox->OnComponentEndOverlap.RemoveDynamic(this, &AVessel::OnEndOverlap);
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
	// If Hidden or Built, use the first FinalRotation value or 0 if there aren't any set
	uint8 rotationAmount = 0;
	if (FinalRotations.Num() > 0) {
		rotationAmount = FinalRotations[0];
	}
	switch (Value) {
		case EVesselBuildStage::Hidden:
			//SetActorHiddenInGame(true);
			CreateTriggerBox();
			break;
		case EVesselBuildStage::Available:
			rotationAmount = FMath::RandRange(0, 3);
		case EVesselBuildStage::Built:		// Both Available and Built do this
			//SetActorHiddenInGame(false);
			RemoveTriggerBox();
			break;
		default:		// Invalid value
			return;
	}
	SetRotationAmount(rotationAmount);
	BuildStage = Value;
}

// Informed by overlap events generated by another Vessel
void AVessel::OnBeginOverlap(AVessel* other)
{
	VesselsOverlapped.push_back(other);
}

void AVessel::OnEndOverlap(AVessel* other)
{
	VesselsOverlapped.remove(other);
}

// Overlap events generated by this Vessel's TriggerBox
void AVessel::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Tell the other Vessel that it is overlaping this
	AVessel* vessel = Cast<AVessel>(OtherActor);
	if (vessel) {
		vessel->OnBeginOverlap(this);
	}
}

void AVessel::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	// Tell the other Vessel it is no longer overlapping this
	AVessel* vessel = Cast<AVessel>(OtherActor);
	if (vessel) {
		vessel->OnEndOverlap(this);
	}
}