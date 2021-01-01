

#include "Components/ActorStatsComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#include "GameModes/RPGGameMode.h"
// Fill out your copyright notice in the Description page of Project Settings.

void ARPGGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ARPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get player pawn
	APawn* tPlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!tPlayerPawn)
	{
		return;
	}

	UActorStatsComponent* tPlayerStats = UActorStatsComponent::GetStatsComponent(tPlayerPawn);

	if (tPlayerStats)
	{
		// Bind PlayerLost function to OnActorKilled delegate
		tPlayerStats->OnActorKilled.AddDynamic(this, &ARPGGameMode::PlayerLost);
	}
}

void ARPGGameMode::AddSouls(int32 SoulsAmountToAdd)
{
	this->m_SoulsAmountCurrent += SoulsAmountToAdd;

	if (this->m_SoulsAmountCurrent >= this->m_SoulsAmountToWin )
	{
		this->m_SoulsAmountCurrent = 0;

		this->PlayerWon();
	}

}

void ARPGGameMode::RemoveSouls(int32 SoulsAmountToRemove)
{
	this->m_SoulsAmountCurrent -= SoulsAmountToRemove;

	FMath::Clamp(this->m_SoulsAmountCurrent, 0, this->m_SoulsAmountToWin);
}

void ARPGGameMode::DecrementSoulsQty()
{
	this->m_SoulsAmountCurrent--;

	FMath::Clamp(this->m_SoulsAmountCurrent, 0, this->m_SoulsAmountToWin);
}

void ARPGGameMode::IncrementPortalsQty()
{
	this->m_PortalsCurrentQty++;
}

void ARPGGameMode::DecrementPortalsQty()
{
	this->m_PortalsCurrentQty--;

	if (this->m_PortalsCurrentQty <= 0)
	{
		this->m_PortalsCurrentQty = 0;

		this->PlayerWon();
	}
}

void ARPGGameMode::PlayerWon()
{
	this->OnPlayerWon.Broadcast();
}

void ARPGGameMode::PlayerLost()
{
	this->OnPlayerLost.Broadcast();
}

void ARPGGameMode::CheckWinningCondition()
{
	////  Check if player has won
	//if (this->m_PortalsCurrentQty <= 0 || this->m_SoulsAmountCurrent >= this->m_SoulsAmountToWin)
	//{
	//	this->OnPlayerWon.Broadcast();
	//}

	//// Get player pawn
	//APawn* tPlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//// Check if player has lost
	//if (tPlayerPawn)
	//{
	//	if()
	//}
}
