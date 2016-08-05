#include "ProjectMishkan.h"
#include "MishkanCamera.h"

AMishkanCamera::AMishkanCamera()
	: ZoomAmount(10), InitialHeight(500)
{

}

void AMishkanCamera::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMishkanCamera, InitialHeight))	{
		ResetHeight();
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMishkanCamera, MaxHeight))	{
		// Make sure it is >= InitialHeight
		if (MaxHeight < InitialHeight) {
			MaxHeight = InitialHeight;
		}
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMishkanCamera, MinHeight))	{
		// Make sure it is <= InitialHeight
		if (MinHeight > InitialHeight) {
			MinHeight = InitialHeight;
		}
	}
	Super::PostEditChangeProperty(e);
}

void AMishkanCamera::ZoomIn()
{
	FVector location = GetActorLocation();
	if ((location.Z - ZoomAmount) >= MinHeight) {
		location.Z -= ZoomAmount;
		SetActorLocation(location);
	}
}

void AMishkanCamera::ZoomOut()
{
	FVector location = GetActorLocation();
	if ((location.Z + ZoomAmount) <= MaxHeight) {
		location.Z += ZoomAmount;
		SetActorLocation(location);
	}
}

void AMishkanCamera::ResetHeight()
{
	FVector location = GetActorLocation();
	location.Z = InitialHeight;
	SetActorLocation(location);
}