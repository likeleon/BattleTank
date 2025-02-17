// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeath);
	FTankDeath OnDeath;

private:
	virtual void BeginPlay();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth = 0;
};
