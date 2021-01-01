// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "GameInstances/RPGGameInstance.h"

URPGGameInstance::URPGGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		this->m_SpellsManager = ObjectInitializer.CreateDefaultSubobject<USpellsManager>(this, TEXT("SpellsManager"));
		this->m_AbilitiesManager = ObjectInitializer.CreateDefaultSubobject<UAbilitiesManager>(this, TEXT("AbilitiesManager"));
		this->m_EffectsManager = ObjectInitializer.CreateDefaultSubobject<UEffectsManager>(this, TEXT("EffectsManager"));
	}
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
}

void URPGGameInstance::Shutdown()
{
}
