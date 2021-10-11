#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void MoveBarrel(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MoveSpeed = 20;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegree = 40;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinDegree = -5;

	bool isLocked = false;
};
