// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* InLeftTrack, UTankTrack* InRightTrack)
{
	LeftTrack = InLeftTrack;
	RightTrack = InRightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack != nullptr)
	{
		LeftTrack->SetThrottle(Throw);
	}
	if (RightTrack != nullptr)
	{
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack != nullptr)
	{
		LeftTrack->SetThrottle(Throw);
	}
	if (RightTrack != nullptr)
	{
		RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector ForwardIntention = MoveVelocity.GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankForward, ForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, ForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
