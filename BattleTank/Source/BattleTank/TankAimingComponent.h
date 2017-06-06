// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelAndTurretReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(const FVector& HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:
	void MoveBarrelAndTurretTowards(const FVector& AimDirection);
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
