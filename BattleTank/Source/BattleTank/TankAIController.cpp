// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	ATank* Tank = GetControlledTank();
	if (Tank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *Tank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
