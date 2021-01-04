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
class LJMUTHIRDPERSON425_API USpellsManager : public UManagerBase
{
	GENERATED_BODY()

public:
	USpellsManager();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ASpell* CreateSpell(TSubclassOf<ASpell> SpellClass);
	UFUNCTION(BlueprintCallable)
	ASpell* CreateSpellFromStruct(const FSpellStruct& SpellStruct);

	virtual void Update(float DeltaTime) override;
	virtual void Clear() override;

private:
	TArray<ASpell*> m_ActiveSpells;
	TArray<ASpell*> m_InactiveSpells;
};
