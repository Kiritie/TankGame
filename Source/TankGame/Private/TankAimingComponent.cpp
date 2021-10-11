#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TankBarrel == nullptr || TankBarrel == nullptr)
		return;
	
	isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTime;
	if(!isReloaded)
		FiringState = EFiringState::Reloading;
	else if(TankTurret->isLocked && TankBarrel->isLocked)
		FiringState = EFiringState::Locked;
	else
		FiringState = EFiringState::Aiming;
}

void UTankAimingComponent::Initialize(UTankTurret * TankTurret, UTankBarrel * TankBarrel)
{
	this->TankTurret = TankTurret;
	this->TankBarrel = TankBarrel;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(TankTurret == nullptr || TankBarrel == nullptr)
		return;

	FVector FireDirection;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("FireLocation"));
	
	bool bHaveSolution = false;
	bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		FireDirection,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveSolution)
	{
		FireDirection = FireDirection.GetSafeNormal();
		TankTurret->MoveTurret(FireDirection);
		TankBarrel->MoveBarrel(FireDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if(TankBarrel == nullptr || ProjectileType == nullptr || !isReloaded)
		return;
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileType,
		TankBarrel->GetSocketLocation(FName("FireLocation")),
		TankBarrel->GetSocketRotation(FName("FireLocation"))
	);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

