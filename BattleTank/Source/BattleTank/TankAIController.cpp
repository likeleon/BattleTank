// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController))
	{
		return;
	}
	
	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = PlayerController->GetPawn();
	if (!ensure(ControlledTank && PlayerTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}
	
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Aiming)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	
	ATank* PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank))
	{
		return;
	}

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
}

void ATankAIController::OnPossessedTankDeath()
{
	if (ensure(GetPawn()))
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}
