// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Spells/Spell.h"
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SpellsManager.generated.h"

struct FSpellStruct;
//class ASpell;

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API ASpellsManager : public AInfo
{
	GENERATED_BODY()

public:
	ASpellsManager();
	ASpell* CreateSpell(const FSpellStruct& SpellStruct);

protected:
private:


public:


private:
	TArray<ASpell*> m_ActiveSpells;
};
