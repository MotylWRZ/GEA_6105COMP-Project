// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

class USpellsManager;
class UAbilitiesManager;
class UEffectsManager;
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

	UFUNCTION(BlueprintPure)
	static UEffectsManager* GetEffectsManager(const UObject* WorldContextObject) { return GetRPGGameInstance(WorldContextObject)->m_EffectsManager; }

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void InitialiseManagers();
	virtual void ResetManagers();
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

public:

private:


	UPROPERTY()
		USpellsManager* m_SpellsManager;

	UPROPERTY()
		UAbilitiesManager* m_AbilitiesManager;

	UPROPERTY()
		UEffectsManager* m_EffectsManager;
};
