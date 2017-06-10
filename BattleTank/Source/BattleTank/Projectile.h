// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void LaunchProjectile(float Speed);

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnDelayedDestroy();

	UPROPERTY(EditDefaultsOnly, Category = Destroy)
	float DestroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Destroy)
	float ProjectileDamage = 20.f;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* ImpactBlast = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent* ExplosionForce = nullptr;

	UProjectileMovementComponent* ProjectileMovement;
};
