#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	void HandleDestruction();
protected:
	void RotateTurret(FVector lookAtTarget);
	void Fire();
private:
//visibleAnywhere,InstanceOnly,DefaultsOnly,EditDefaultsOnly, BlueprintReadWrite 
	//forward typying class
	//cuz pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* capsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* baseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* turretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* projectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* deathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* deathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> deathCameraShakeClass;
};