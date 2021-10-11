#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	this->Throttle = Throttle;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AddMotorForce();
	AddSideForce();
}

void UTankTrack::AddMotorForce()
{
	FVector MotorForce = GetForwardVector() * MaxMotorForce * Throttle;
	FVector ForceLocation = GetSocketLocation(FName("ForceLocation"));
	auto TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankBody->AddForceAtLocation(MotorForce, ForceLocation);
	Throttle = 0;
}

void UTankTrack::AddSideForce()
{
	auto TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	FVector TankVelocity = TankBody->GetComponentVelocity();
	FVector RightVector = TankBody->GetRightVector();
	//获取坦克侧滑的速度
	float SideSpeed = FVector::DotProduct(TankVelocity, RightVector);
	//获取坦克侧滑对应的加速度
	FVector SideAcceleration = (SideSpeed / GetWorld()->DeltaTimeSeconds) * RightVector;
	//f = m * a
	FVector SideForce = (TankBody->GetMass() * SideAcceleration) / 2;
	TankBody->AddForce(-SideForce);
}
