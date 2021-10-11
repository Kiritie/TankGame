#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.generated.h"

UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure)
	ATank* GetControlledTank();

	UFUNCTION(BlueprintPure)
	ATank* GetPlayerTank();

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 1000.0f;

private:
	ATank* ControlledTank;

	ATank* PlayerTank;
};
