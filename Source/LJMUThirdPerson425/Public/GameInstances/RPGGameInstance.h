// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Managers/SpellsManager.h"

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
	URPGGameInstance();

	UFUNCTION()
	FORCEINLINE ASpellsManager* const GetSpellsManager() const { return m_SpellsManager; }

	virtual void Init() override;

public:


private:
	ASpellsManager* m_SpellsManager;

};
