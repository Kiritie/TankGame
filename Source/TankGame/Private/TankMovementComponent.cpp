#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::HandleTankMovement(float ForwardAxis, float TurningAxis)
{
	float LeftTrackThrottle = 0;
	float RightTrackThrottle = 0;
	if(ForwardAxis == 0)
	{
		LeftTrackThrottle = TurningAxis;
		RightTrackThrottle = -TurningAxis;
	}
	else
	{
		LeftTrackThrottle = RightTrackThrottle = ForwardAxis;
		if(TurningAxis != 0)
		{
			if(ForwardAxis > 0)
			{
				if(TurningAxis < 0)
					RightTrackThrottle -= TurningAxis;
				else
					LeftTrackThrottle += TurningAxis;
			}
			else
			{
				if(TurningAxis < 0)
					RightTrackThrottle += TurningAxis;
				else
					LeftTrackThrottle -= TurningAxis;
			}
		}
	}
	LeftTrack->SetThrottle(LeftTrackThrottle);
	RightTrack->SetThrottle(RightTrackThrottle);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector MoveVelocityNormal = MoveVelocity.GetSafeNormal();
	FVector TankForwardVector = GetOwner()->GetActorForwardVector();
	FVector TankRightVector = GetOwner()->GetActorRightVector();

	float ForwardSpeed = FVector::DotProduct(MoveVelocityNormal, TankForwardVector);
	float RightSpeed = FVector::DotProduct(MoveVelocityNormal, TankRightVector);

	HandleTankMovement(FMath::Sign(ForwardSpeed), FMath::Sign(RightSpeed));
}
