// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetControlledTank() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrossHairYLocation = 1 / 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LineTraceRange = 10 * 1000 * 100; // 10km

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
};
