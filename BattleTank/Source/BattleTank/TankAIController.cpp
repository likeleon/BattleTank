// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(ControlledTank && PlayerTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}