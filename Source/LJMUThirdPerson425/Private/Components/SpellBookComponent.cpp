// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "GameInstances/RPGGameInstance.h"

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

	const FSpellStruct& tSpellStruct = *this->m_SpellsList[SpellID];

	URPGGameInstance* tRPGGameInstance = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));

	// Spawn a new spell using the SpellStruct
	ASpell* tNewSpell = tRPGGameInstance->GetSpellsManager()->CreateSpell(tSpellStruct);

	// Check if there is enough mana to cast the spell
	if (this->m_Mana >= tSpellStruct.ManaCost)
	{
		// Take required mana to cast the spell
		this->TakeMana(tSpellStruct.ManaCost);

		if (!tNewSpell->CastSpell(this->GetOwner()))
		{
			UE_LOG(LogTemp, Error, TEXT("Spell casting unsuccesful"));
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not enought mana to cast the spell"));

		return;
	}
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

void USpellBookComponent::ModifyMana(int32 ModifyingValue)
{
	int32 OldMana = this->m_Mana;
	int32 NewMana = FMath::Clamp(this->m_Mana + ModifyingValue, 0, this->m_ManaMax);

	int32 Delta = NewMana - OldMana;

	this->m_Mana = NewMana;

	if (Delta != 0)
	{
		// MulticastHealthChanged
		if (Delta > 0)
		{
			// MulticastOnManaAdded
		}
		else
		{
			// MulticastOnManaTaken
		}
	}

	if (Delta < 0)
	{
		// MulticastOnMana = 0
	}
}

void USpellBookComponent::ModifyManaMax(int32 ModifyingValue)
{
	int32 OldManaMax = this->m_ManaMax;
	int32 NewManaMax = this->m_ManaMax + ModifyingValue;

	if (this->m_Mana > NewManaMax)
	{
		this->m_Mana = FMath::Clamp(this->m_Mana, 0, NewManaMax);
	}

	this->m_ManaMax = NewManaMax;
}

void USpellBookComponent::AddMana(int32 ManaToAdd)
{
	this->ModifyMana(ManaToAdd);
}

void USpellBookComponent::TakeMana(int32 ManaToTake)
{
	this->ModifyMana(-ManaToTake);
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

