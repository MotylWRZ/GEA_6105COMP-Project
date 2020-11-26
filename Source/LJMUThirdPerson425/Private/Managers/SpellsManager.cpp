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

	return tNewSpell;

	this->m_ActiveSpells.Add(tNewSpell);
}
