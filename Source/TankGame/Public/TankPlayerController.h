#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "CollisionQueryParams.h"
#include "TankPlayerController.generated.h"

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	ATank* GetControlledTank();

	void AimToTarget();

	bool GetSightRayHitLocation(FVector &HitLocation);

	UPROPERTY(EditAnywhere)
	AActor* AimPoint;

private:
	ATank* ControlledTank = nullptr;
};