// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* InBarrel, UTankTurret* InTurret)
{
	Barrel = InBarrel;
	Turret = InTurret;
}

void UTankAimingComponent::AimAt(const FVector& HitLocation)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (!UGameplayStatics::SuggestProjectileVelocity(
		this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		return;
	}

	MoveBarrelAndTurretTowards(LaunchVelocity.GetSafeNormal());
}

void UTankAimingComponent::MoveBarrelAndTurretTowards(const FVector& AimDirection)
{
	check(Barrel != nullptr && Turret != nullptr);

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!bIsReloaded)
	{
		return;
	}

	FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
	Projectile->LaunchProjectile(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();
}