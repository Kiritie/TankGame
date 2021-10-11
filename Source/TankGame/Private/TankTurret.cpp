#include "TankTurret.h"

void UTankTurret::MoveTurret(FVector AimDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	float AngleYaw = AimRotation.Yaw - CurrentRotation.Yaw;
	if(AngleYaw > 180)
		AngleYaw -= 360;
	else if(AngleYaw < -180)
		AngleYaw += 360;

	float DeltaYaw = FMath::Clamp<float>(AngleYaw, -1, 1);
	DeltaYaw *= MoveSpeed * GetWorld()->DeltaTimeSeconds;
	if(FMath::Abs(DeltaYaw) > FMath::Abs(AngleYaw))
		DeltaYaw = AngleYaw;
	isLocked = FMath::Abs(AngleYaw) < 3;

	AddRelativeRotation(FRotator(0, DeltaYaw, 0));
}
