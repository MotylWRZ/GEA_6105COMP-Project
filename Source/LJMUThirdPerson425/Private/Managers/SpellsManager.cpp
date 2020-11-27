// Fill out your copyright notice in the Description page of Project Settings.

#include "Spells/Spell.h"

#include "Managers/SpellsManager.h"


ASpellsManager::ASpellsManager()
{

}

ASpell* ASpellsManager::CreateSpell(const FSpellStruct& SpellStruct)
{
	ASpell* tNewSpell;

	// Check if Spell Class is set
	if (SpellStruct.SpellClass)
	{
		// If it is set, spawn the Spell using the SpellClass from struct
		tNewSpell = GetWorld()->SpawnActor<ASpell>(SpellStruct.SpellClass);
	}
	else
	{
		// If it is not set, spawn the basic Spell
		tNewSpell = GetWorld()->SpawnActor<ASpell>(ASpell::StaticClass());

		// Set the SpellStruct for the newly created spell
		tNewSpell->Initialise(SpellStruct);
	}

	if (tNewSpell)
	{
		this->m_ActiveSpells.Add(tNewSpell);

		this->SetShouldUpdate(true);
	}

	return tNewSpell;


}

void ASpellsManager::Update()
{
	AManagerBase::Update();

	// Update all spells
	for (int32 i = this->m_ActiveSpells.Num() - 1; i >= 0; --i)
	{
		ASpell* tSpell = m_ActiveSpells[i];

		if (!tSpell->IsSpellActive())
		{
			// Destroy and clear inactive spell
			this->m_ActiveSpells.RemoveSwap(tSpell);
			tSpell->AutoDestroy();
		}
	}

	if (this->m_ActiveSpells.Num() == 0)
	{
		// Stop updating this manager
		this->SetShouldUpdate(false);
	}
}
