// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Spells/Spell.h"
#include "Managers/ManagerBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SpellsManager.generated.h"

struct FSpellStruct;
//class ASpell;

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API ASpellsManager : public AManagerBase
{
	GENERATED_BODY()

public:
	ASpellsManager();

	UFUNCTION(BlueprintCallable)
	ASpell* CreateSpell(const FSpellStruct& SpellStruct);

	virtual void Update() override;
	virtual void Clear() override;

protected:

private:


public:


private:
	TArray<ASpell*> m_ActiveSpells;
	TArray<ASpell*> m_InactiveSpells;
};
