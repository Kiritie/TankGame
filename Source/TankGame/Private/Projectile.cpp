#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->SetAutoActivate(false);

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	SetRootComponent(CollisionMesh);

	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchParticle"));
	LaunchParticle->SetAutoActivate(false);
	LaunchParticle->AttachTo(RootComponent);

	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("HitParticle"));
	HitParticle->SetAutoActivate(false);
	HitParticle->AttachTo(RootComponent);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->SetAutoActivate(false);
	ExplosionForce->AttachTo(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	LaunchParticle->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitParticle->Activate();
	
	CollisionMesh->SetNotifyRigidBodyCollision(false);
	SetRootComponent(HitParticle);
	CollisionMesh->DestroyComponent();

	ExplosionForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(
		this,
		MaxDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);
}