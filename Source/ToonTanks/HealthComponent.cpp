#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGamemode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	toonTanksGamemode = Cast<AToonTanksGamemode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damagetype, class AController* instigator, AActor* damageCauser)
{
	if (damage <= 0.0f) return;

	health -= damage;
	UE_LOG(LogTemp, Warning, TEXT("DamageTaken %f"),health);

	if (health <= 0 && toonTanksGamemode!=nullptr)
	{
		toonTanksGamemode->ActorDied(damagedActor);
	}
}