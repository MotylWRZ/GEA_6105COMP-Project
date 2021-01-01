// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/EffectsManager.h"
#include "Managers/SpellsManager.h"
#include "Managers/AbilitiesManager.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/CoreDelegates.h"
#include "Engine/World.h"

#include "GameInstances/RPGGameInstance.h"




URPGGameInstance::URPGGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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
	Super::Init();

}

void URPGGameInstance::Shutdown()
{
	Super::Shutdown();
}

void URPGGameInstance::InitialiseManagers()
{
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		this->m_SpellsManager = NewObject<USpellsManager>(this, TEXT("SpellsManager"));
		this->m_AbilitiesManager = NewObject<UAbilitiesManager>(this, TEXT("AbilitiesManager"));
		this->m_EffectsManager = NewObject<UEffectsManager>(this, TEXT("EffectsManager"));
	}
}

void URPGGameInstance::ResetManagers()
{
	// Make all the pointers to manager NULL to allow them to be garbage collected
	this->m_AbilitiesManager = NULL;
	this->m_EffectsManager = NULL;
	this->m_SpellsManager = NULL;

	// Create new manager objects
	this->InitialiseManagers();
}

void URPGGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	// Reinitialise managers if the map has been changed
	if (NewWorld)
	{
		this->ResetManagers();
	}
}
