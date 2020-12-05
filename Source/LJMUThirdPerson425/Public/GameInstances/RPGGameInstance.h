// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Managers/SpellsManager.h"
#include "Managers/AbilitiesManager.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"


/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URPGGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	static URPGGameInstance* GetRPGGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure)
	static USpellsManager* GetSpellsManager (const UObject* WorldContextObject) { return GetRPGGameInstance(WorldContextObject)->m_SpellsManager; }

	UFUNCTION(BlueprintPure)
	static UAbilitiesManager* GetAbilitiesManager(const UObject* WorldContextObject) { return GetRPGGameInstance(WorldContextObject)->m_AbilitiesManager; }

	virtual void Init() override;

public:

private:


	UPROPERTY()
		USpellsManager* m_SpellsManager;

	UPROPERTY()
		UAbilitiesManager* m_AbilitiesManager;
};
