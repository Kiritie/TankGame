#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* TankBody = Cast<UPrimitiveComponent>(RootComponent);
	TankBody->SetCenterOfMass(TankBody->GetComponentTransform().InverseTransformPosition(TankBody->GetSocketLocation(FName("MassCenter"))));
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageValue = FMath::Clamp<int32>(FMath::RoundToInt(Damage), 0, MaxHP);
	CurrentHP -= DamageValue;
	if(CurrentHP <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Dead, Tank Name: %s"), *GetName());
	}
	return DamageValue;
}

float ATank::GetPercentHP()
{
	return (float)CurrentHP / (float)MaxHP;
}