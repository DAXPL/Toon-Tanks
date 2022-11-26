#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}
void ABasePawn::HandleDestruction()
{
	if (deathParticles) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, deathParticles, GetActorLocation(), GetActorRotation());
	}
	if (deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	}
	if (deathCameraShakeClass) 
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
	}
}
void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector toTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.0f, toTarget.Rotation().Yaw, 0.0f);
	turretMesh->SetWorldRotation(
		FMath::RInterpTo(
			turretMesh->GetComponentRotation(), 
			lookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this),
			2.5f));
}
void ABasePawn::Fire() 
{
	FVector projectileSpawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator projectileSpawnRotation = projectileSpawnPoint->GetComponentRotation();

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, projectileSpawnLocation, projectileSpawnRotation);
	projectile->SetOwner(this);
	//DrawDebugSphere(GetWorld(), projectileSpawnPointLocation, 25.0f, 12, FColor::Red, false, 3.0f);
}