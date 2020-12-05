// Fill out your copyright notice in the Description page of Project Settings.

#include "Spells/Spell.h"

#include "Managers/SpellsManager.h"


USpellsManager::USpellsManager()
{

}

void USpellsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update all spells
	for (int32 i = this->m_ActiveSpells.Num() - 1; i >= 0; --i)
	{
		ASpell* tSpell = m_ActiveSpells[i];

		if (!tSpell->IsSpellActive())
		{
			this->m_InactiveSpells.Add(tSpell);
		}
	}
	// Remove all inactive pointers from the Active array
	m_ActiveSpells.RemoveAll([](ASpell* Spell)
		{
			return !Spell->IsSpellActive();
		});

	if (this->ShouldClear())
	{
		this->Clear();
	}

	if (this->m_ActiveSpells.Num() == 0 && this->m_InactiveSpells.Num() == 0)
	{
		// Stop updating this manager
		this->SetShouldUpdate(false);
	}
}

ASpell* USpellsManager::CreateSpell(TSubclassOf<ASpell> SpellClass)
{
	ASpell* tNewSpell;
	tNewSpell = GetWorld()->SpawnActor<ASpell>(SpellClass);

	if (tNewSpell)
	{
		this->m_ActiveSpells.Add(tNewSpell);

		this->SetShouldUpdate(true);
	}

	return tNewSpell;
}

ASpell* USpellsManager::CreateSpellFromStruct(const FSpellStruct& SpellStruct)
{
	ASpell* tNewSpell;

	// Check if Spell Class is set
	if (SpellStruct.bUseCompleteSpellClass)
	{
		if (!SpellStruct.SpellClass)
		{
				UE_LOG(LogTemp, Error, TEXT("%s spell with ID '%i' cannot be spawned. It is set to use complete Spell Class. Please provide a complete Spell Class or set bUseCompleteSpellClass to false if the Spell should be customised directly in SpellBook."), *SpellStruct.SpellName.ToString(), SpellStruct.SpellID);
				return nullptr;
		}
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

void USpellsManager::Update(float DeltaTime)
{
	//USpellsManager::Update();

	//// Update all spells
	//for (int32 i = this->m_ActiveSpells.Num() - 1; i >= 0; --i)
	//{
	//	ASpell* tSpell = m_ActiveSpells[i];

	//	if (!tSpell->IsSpellActive())
	//	{
	//		this->m_InactiveSpells.Add(tSpell);
	//	}
	//}
	//// Remove all inactive pointers from the Active array
	//m_ActiveSpells.RemoveAll([](ASpell* Spell)
	//	{
	//		return !Spell->IsSpellActive();
	//	});

	//if (this->ShouldClear())
	//{
	//	this->Clear();
	//}

	//if (this->m_ActiveSpells.Num() == 0 && this->m_InactiveSpells.Num() == 0)
	//{
	//	// Stop updating this manager
	//	this->SetShouldUpdate(false);
	//}
}

void USpellsManager::Clear()
{
	Super::Clear();

	for (int32 i = this->m_InactiveSpells.Num() - 1; i >= 0; --i)
	{
		this->m_InactiveSpells[i]->AutoDestroy();
	}
	m_InactiveSpells.Empty();
}
