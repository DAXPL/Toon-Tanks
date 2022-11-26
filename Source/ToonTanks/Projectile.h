// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* projectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float damage = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* hitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* trailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* launchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> hitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
