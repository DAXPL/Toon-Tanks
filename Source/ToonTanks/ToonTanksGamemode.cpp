// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGamemode::BeginPlay() 
{
	Super::BeginPlay();
	HandleGameStart();	
}
void AToonTanksGamemode::HandleGameStart()
{
	targetTowersCount = GetTargetCount();

	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if(toonTanksPlayerController)
	{
		toonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle playerEnableTimerHandle;
		FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			toonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			playerEnableTimerHandle,
			playerEnableTimerDelegate,
			startDelay,
			false
		);
	}
}
void AToonTanksGamemode::ActorDied(AActor* deadActor)
{
	if (deadActor == tank && tank!=nullptr) 
	{
		tank->HandleDestruction();
		if (toonTanksPlayerController)
		{
			toonTanksPlayerController->SetPlayerEnabledState(false);
		}	
		GameOver(false);
	}
	else if(ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->HandleDestruction();
		--targetTowersCount;
		if(targetTowersCount <= 0)
		{
			GameOver(true);
		}
	}
}
int32 AToonTanksGamemode::GetTargetCount()
{
	TArray<AActor*> towers;//wskazniki do wszystkich wierz na mapie
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}