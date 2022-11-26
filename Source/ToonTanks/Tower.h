// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
private:
	class ATank* tank;
	UPROPERTY(EditDefaultsOnly, Category="Combat");
	float fireRange = 300.0f;

	FTimerHandle fireRateHandle;
	float fireRate = 2.0f;
	void CheckFireCondition();

	bool InFireRange();
};
