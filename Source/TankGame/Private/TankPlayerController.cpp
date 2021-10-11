#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	AimToTarget();
}

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToTarget()
{
	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation))
	{
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector WorldLocation;
	FVector WorldDirection;
	if(DeprojectScreenPositionToWorld(ViewportSizeX * 0.5f, ViewportSizeY * 0.35f, WorldLocation, WorldDirection))
	{
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = WorldDirection * 1000000;
		FHitResult HitResult;
		if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, FCollisionQueryParams(NAME_None, false, ControlledTank)))
		{
			HitLocation = HitResult.ImpactPoint;
			if(AimPoint != nullptr)
			{
				AimPoint->SetActorLocation(HitLocation);
			}
			return true;
		}
	}
	return false;
}
