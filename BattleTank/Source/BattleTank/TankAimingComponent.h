// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

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

	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* InBarrel, UTankTurret* InTurret);

	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunc) override;

	void MoveBarrelAndTurretTowards();
	bool IsBarrelMoving() const;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0.0;

	FVector AimDirection;
};
