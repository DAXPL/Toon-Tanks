#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	float maxHealth = 100.0f;
	float health = 0.0f;
	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damagetype, class AController* instigator, AActor* damageCauser);

	class AToonTanksGamemode* toonTanksGamemode;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
