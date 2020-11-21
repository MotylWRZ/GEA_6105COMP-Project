// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpellBookComponent.h"

// Sets default values for this component's properties
USpellBookComponent::USpellBookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USpellBookComponent::CastSpell(int32 SpellID)
{

	// Try to find the spell with given ID
	if (!this->m_SpellsList.Find(SpellID))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the Spell with given ID"));

		return;
	}

	ASpell* tNewSpell;

	// Check if Spell Class is set
	if (m_SpellsList[SpellID]->SpellClass)
	{
		// If it is set, spawn the Spell using the SpellClass from struct
		tNewSpell = GetWorld()->SpawnActor<ASpell>(m_SpellsList[SpellID]->SpellClass, this->GetOwner()->GetActorLocation(),
			this->GetOwner()->GetActorRotation());
	}
	else
	{
		// If it is not set, spawn the basic Spell
		tNewSpell = GetWorld()->SpawnActor<ASpell>(ASpell::StaticClass(), this->GetOwner()->GetActorLocation(),
			this->GetOwner()->GetActorRotation());

		// Set the SpellStruct for the newly created spell
		tNewSpell->Initialise(*this->m_SpellsList[SpellID]);
	}



	tNewSpell->CastSpell(this->GetOwner());

	m_ActiveSpells.Add(tNewSpell);
}

// Called when the game starts
void USpellBookComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& tSpellStruct : m_Spells)
	{
		// Create a new ID for the Spell
		int32 tNewSpellID = m_SpellsList.Num() + 1;

		// Assign spell ID to the Spell structure
		tSpellStruct.SpellID = tNewSpellID;

		m_SpellsList.Add(tNewSpellID, &tSpellStruct);
	}

	if (this->m_bUseSpellsDataTable)
	{
		if (!m_SpellsDT)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot load Spells Data Table."));

			return;
		}
		LoadDataTable(this->m_SpellsDT);
	}

	InitialiseMagicSpheres();
}

void USpellBookComponent::LoadDataTable(UDataTable* DataTable)
{
	for (auto& tRow : DataTable->GetRowMap())
	{
		FSpellStruct* SpellStructure = reinterpret_cast<FSpellStruct*>(tRow.Value);

		// Create a new ID for the Spell
		int32 tNewSpellID = m_SpellsList.Num() + 1;

		// Assign spell ID to the Spell structure
		SpellStructure->SpellID = tNewSpellID;

		m_SpellsList.Add(tNewSpellID, SpellStructure);
	}
}

// Called every frame
void USpellBookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellBookComponent::InitialiseMagicSpheres()
{
	if (!this->m_MagicSpheresDT)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot load Magic Spheres Data Table."));

		return;
	}

	for (auto& tRow : this->m_MagicSpheresDT->GetRowMap())
	{
		FMagicSphere SphereStructure = *reinterpret_cast<FMagicSphere*>(tRow.Value);

		// Load all the spells from this Magic Sphere into the the SphereStruct
		for (auto& tSpellsMapElem : this->m_SpellsList)
		{
			if (tSpellsMapElem.Value->MagicSphereType == SphereStructure.MagicSphereType)
			{
					SphereStructure.Spells.Add(*tSpellsMapElem.Value);
			}

		}
		m_MagicSpheres.Add(SphereStructure.MagicSphereType, SphereStructure);
	}
}

