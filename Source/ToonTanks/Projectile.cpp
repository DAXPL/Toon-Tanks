#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
	projectileMovement->MaxSpeed = 1300.0f;
	projectileMovement->InitialSpeed = 1350.0f;

	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail"));
	trailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit) 
{
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr) 
	{
		Destroy();
		return;
	} 

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor && otherActor != myOwner) 
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, myOwnerInstigator, this, damageTypeClass);
		if (hitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticles, GetActorLocation(), GetActorRotation());
		}	
		if (hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
		if(hitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
		}
	}
	Destroy();
	//UE_LOG(LogTemp, Warning, TEXT("OnHit %s %s %s"), *hitComp->GetName(), *otherActor->GetName(), *otherComp->GetName());
}