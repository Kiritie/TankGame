#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(ControlledTank == nullptr || PlayerTank == nullptr)
		return;

	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* TankAiming = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAiming->AimAt(PlayerTank->GetActorLocation());
	if(TankAiming->FiringState == EFiringState::Locked)
		TankAiming->Fire();
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
}