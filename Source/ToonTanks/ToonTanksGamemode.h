// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGamemode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* deadActor);
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
private:
	class ATank* tank;
	class AToonTanksPlayerController* toonTanksPlayerController;

	float startDelay = 3.0f;
	void HandleGameStart();

	int32 targetTowersCount = 0;
	int32 GetTargetCount();
};
