#include "TankBarrel.h"

void UTankBarrel::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	float AnglePitch = FMath::Clamp<float>(AimRotation.Pitch, MinDegree, MaxDegree) - CurrentRotation.Pitch;

	float DeltaPitch = FMath::Clamp<float>(AnglePitch, -1, 1);
	DeltaPitch *= MoveSpeed * GetWorld()->DeltaTimeSeconds;
	if(FMath::Abs(DeltaPitch) > FMath::Abs(AnglePitch))
		DeltaPitch = AnglePitch;
	isLocked = FMath::Abs(AnglePitch) < 0.3;

	float TargetPitch = FMath::Clamp<float>(RelativeRotation.Pitch + DeltaPitch, MinDegree, MaxDegree);

	SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
