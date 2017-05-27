// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	ATank* Tank = GetControlledTank();
	if (Tank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *Tank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
