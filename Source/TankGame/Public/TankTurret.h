#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void MoveTurret(FVector AimDirection);
	
	UPROPERTY(EditAnywhere, Category="Setup")
	float MoveSpeed = 20;

	bool isLocked = false;
};
