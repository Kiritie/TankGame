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
	//��ȡ̹�˲໬���ٶ�
	float SideSpeed = FVector::DotProduct(TankVelocity, RightVector);
	//��ȡ̹�˲໬��Ӧ�ļ��ٶ�
	FVector SideAcceleration = (SideSpeed / GetWorld()->DeltaTimeSeconds) * RightVector;
	//f = m * a
	FVector SideForce = (TankBody->GetMass() * SideAcceleration) / 2;
	TankBody->AddForce(-SideForce);
}
