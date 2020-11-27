// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "GameInstances/RPGGameInstance.h"

URPGGameInstance::URPGGameInstance()
{


}

URPGGameInstance* URPGGameInstance::GetRPGGameInstance(const UObject* WorldContextObject)
{
	URPGGameInstance* tRPGgameInstance = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (tRPGgameInstance)
	{
		return tRPGgameInstance;
	}

	UE_LOG(LogTemp, Error, TEXT("RPGgameInstance is null ! Please make sure that RPGgameInstance is set in the project settings."));
	return nullptr;
}

void URPGGameInstance::Init()
{
	// Create an instance of SpellsManager
	this->m_SpellsManager = GetWorld()->SpawnActor<ASpellsManager>(ASpellsManager::StaticClass());

	// Create an instance of AbilitiesManager
	this->m_AbilitiesManager = GetWorld()->SpawnActor<AAbilitiesManager>(AAbilitiesManager::StaticClass());
}
