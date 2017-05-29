// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *Tank->GetName());
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *PlayerTank->GetName())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (ControlledTank != nullptr && PlayerTank != nullptr)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		return Cast<ATank>(PlayerController->GetPawn());
	}
	return nullptr;
}
