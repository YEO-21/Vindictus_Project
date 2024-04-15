#include "Component/ZoomableSpringArmComponent/ZoomableSpringArmComponent.h"

UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{
	ZoomMultiplier = 20.0f;

	ZoomLengthMin = 150.0f;
	ZoomLengthMax = 500.0f;
}

void UZoomableSpringArmComponent::ZoomCamera(float axis)
{
	TargetArmLength -= axis * ZoomMultiplier;
	TargetArmLength = FMath::Clamp(TargetArmLength, ZoomLengthMin, ZoomLengthMax);
}
