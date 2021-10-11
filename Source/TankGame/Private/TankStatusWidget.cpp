#include "TankStatusWidget.h"

void UTankStatusWidget::OrientToCamera()
{
	FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FQuat TargetRot = FQuat((CameraLocation - GetComponentLocation()).Rotation());
	TargetRot = GetOwner()->GetRootComponent()->GetComponentTransform().InverseTransformRotation(TargetRot);
	TargetRot = FQuat(FRotator(0, TargetRot.Rotator().Yaw, 0));
	SetRelativeRotation(TargetRot);
}