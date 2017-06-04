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
	UE_LOG(LogTemp, Warning, TEXT("%s request move at %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}
