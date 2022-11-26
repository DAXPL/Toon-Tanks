// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return tankPlayerController; }

	bool bAlive = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* camera;
	UPROPERTY(EditAnywhere, Category="Movement",meta=(AllowPrivateAccess = "true"))
	float speed = 200.0f;
	UPROPERTY(EditAnywhere, Category="Movement",meta=(AllowPrivateAccess = "true"))
	float turnRate = 50.0f;

	void Move(float value);
	void Turn(float value);
	
	APlayerController* tankPlayerController;

public:	
	virtual void Tick(float DeltaTime) override;
};
