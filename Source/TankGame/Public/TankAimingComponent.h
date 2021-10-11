#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankTurret* TankTurret, UTankBarrel* TankBarrel);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="TankEvent")
	void Fire();

	UPROPERTY(EditAnywhere, Category="Setup")
	float LaunchSpeed = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileType;

	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Aiming;

private:
	UTankTurret* TankTurret;
	
	UTankBarrel* TankBarrel;

	bool isReloaded = false;

	double LastFireTime = 0;
};
