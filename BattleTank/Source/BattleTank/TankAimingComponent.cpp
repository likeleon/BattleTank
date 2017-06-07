// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* InBarrel, UTankTurret* InTurret)
{
	Barrel = InBarrel;
	Turret = InTurret;
	
	AimDirection = Barrel->GetForwardVector();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunc)
{
	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel))
	{
		return false;
	}
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
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

	AimDirection = LaunchVelocity.GetSafeNormal();

	MoveBarrelAndTurretTowards();
}

void UTankAimingComponent::MoveBarrelAndTurretTowards()
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
	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}

	if (FiringState == EFiringState::Reloading)
	{
		return;
	}

	FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
	Projectile->LaunchProjectile(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();
}