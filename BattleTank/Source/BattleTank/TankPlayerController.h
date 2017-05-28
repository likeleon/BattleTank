// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairYLocation = 1 / 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineTraceRange = 10 * 1000 * 100; // 10km

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
};
