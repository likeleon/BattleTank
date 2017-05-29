// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreePerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barel-Elevate() called at speed %f"), DegreePerSecond);
}
