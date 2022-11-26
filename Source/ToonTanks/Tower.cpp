// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay() 
{
	Super::BeginPlay();
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(fireRateHandle, this, &ATower::CheckFireCondition, fireRate, true);
}
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(tank->GetActorLocation());
	}
	
}
void ATower::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}
void ATower::CheckFireCondition()
{
	if (tank == nullptr) 
	{
		return;
	}
	if (InFireRange() && tank->bAlive)
	{
		Fire();
	}
}
bool ATower::InFireRange() 
{
	if (tank) 
	{
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		if (distance <= fireRange)
		{
			return true;
		}
	}
	return false;
}