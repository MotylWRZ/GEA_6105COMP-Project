// Fill out your copyright notice in the Description page of Project Settings.
#include "GameInstances/RPGGameInstance.h"
#include "Managers/SpellsManager.h"

#include "Components/SpellBookComponent.h"

// Sets default values for this component's properties
USpellBookComponent::USpellBookComponent()
	: m_Mana(10)
	, m_ManaMax(20)
	, m_ManaRegenerationAmount(1)
	, m_ManaRegenerationInterval(1.0f)
	, m_SpellCastCooldown(0.5f)
	, m_bIsCooledDown(true)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}


void USpellBookComponent::CastSpell(int32 SpellID)
{
	if (!this->CanCastSpell())
	{
		return;
	}



	// Try to find the spell with given ID
	if (!this->m_SpellsList.Find(SpellID))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the Spell with given ID"));

		return;
	}

	const FSpellStruct& tSpellStruct = this->m_SpellsList[SpellID];

	USpellsManager* tSpellsManager = URPGGameInstance::GetSpellsManager(this);

	// Check if there is enough mana to cast the spell
	if (this->m_Mana >= tSpellStruct.ManaCost)
	{
		//URPGGameInstance::GetRPGGameInstance(this);
		if (!tSpellsManager)
		{
			return;
		}

		// Spawn a new spell using the SpellStruct
		ASpell* tNewSpell = tSpellsManager->CreateSpellFromStruct(tSpellStruct);

		// Take required mana to cast the spell
		this->TakeMana(tSpellStruct.ManaCost);

		if (!tNewSpell->CastSpell(this->GetOwner()))
		{
			UE_LOG(LogTemp, Error, TEXT("Spell casting unsuccesful"));
			this->OnSpellCast.Broadcast(false);
			return;
		}

		// Mark the IsCooledDown as false in order to avoid spell overcasting
		this->m_bIsCooledDown = false;

		// Initialise and run SpellbookCooldownTimer with the delay equal to CaseSpellCoooldown duration value
		GetWorld()->GetTimerManager().SetTimer(this->m_SpellbookCooldownTimerHandle, this, &USpellBookComponent::ResetSpellCastCooldown, this->m_SpellCastCooldown);
		this->OnCooldownChange.Broadcast();
		this->OnSpellCast.Broadcast(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not enough mana to cast the spell"));

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

		if (tSpellStruct.bUseCompleteSpellClass)
		{
			if (!this->LoadSpellStructFromCompleteClass(tSpellStruct))
			{
				continue;
			}
		}

		// Clear custom abilities arrays if bCustomAbilities flag is set to false
		// This will help to save some space as they won't be used, therefore there is no need to store them
		if (!tSpellStruct.bCustomiseAbilities)
		{
			this->ClearCustomAbilities(tSpellStruct);
		}

		// Assign spell ID to the Spell structure
		tSpellStruct.SpellID = tNewSpellID;

		m_SpellsList.Add(tNewSpellID, tSpellStruct);
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


	// Initialise SpellbookManaTimer
	GetWorld()->GetTimerManager().SetTimer(this->m_SpellbookManaTimerHandle, this, &USpellBookComponent::RegenerateMana, this->m_ManaRegenerationInterval, true);
}

void USpellBookComponent::LoadDataTable(UDataTable* DataTable)
{
	for (auto& tRow : DataTable->GetRowMap())
	{
		// Create a Spell structure from the structure stored in data table
		FSpellStruct tSpellStructure = *reinterpret_cast<FSpellStruct*>(tRow.Value);

		// Create a new ID for the Spell
		int32 tNewSpellID = m_SpellsList.Num() + 1;

		if (tSpellStructure.bUseCompleteSpellClass)
		{
			if (!this->LoadSpellStructFromCompleteClass(tSpellStructure))
			{
				continue;
			}
		}

		// Clear custom abilities arrays if bCustomAbilities flag is set to false
		// This will help to save some space as they won't be used, therefore there is no need to store them
		if (!tSpellStructure.bCustomiseAbilities)
		{
			this->ClearCustomAbilities(tSpellStructure);
		}

		// Assign spell ID to the Spell structure
		tSpellStructure.SpellID = tNewSpellID;

		m_SpellsList.Add(tNewSpellID, tSpellStructure);
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
		// Call the delegate OnManaModified
		this->OnManaModified.Broadcast();

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

void USpellBookComponent::ModifyManaRegenerationAmount(int32 ModifyingValue)
{
	int32 tNewManaRegenerationAmount = this->m_ManaRegenerationAmount + ModifyingValue;

	if (tNewManaRegenerationAmount <= 0)
	{
		tNewManaRegenerationAmount = 0;
	}

	this->m_ManaRegenerationAmount = tNewManaRegenerationAmount;
}

void USpellBookComponent::ModifyManaRegenerationInterval(float ModifyingValue)
{
	int32 tNewManaRegenerationInterval = this->m_ManaRegenerationInterval + ModifyingValue;

	if (tNewManaRegenerationInterval <= 0.0f)
	{
		tNewManaRegenerationInterval = 0.0f;
	}

	this->m_ManaRegenerationAmount = tNewManaRegenerationInterval;
}

bool USpellBookComponent::CanCastSpell()
{
	return this->m_bIsCooledDown;
}

void USpellBookComponent::RegenerateMana()
{
	this->ModifyMana(this->m_ManaRegenerationAmount);
}

void USpellBookComponent::ResetSpellCastCooldown()
{
	this->m_bIsCooledDown = true;
	this->OnCooldownChange.Broadcast();
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
		// Create a Sphere structure from the structure stored in data table
		FMagicSphere SphereStructure = *reinterpret_cast<FMagicSphere*>(tRow.Value);

		// Load all the spells from this Magic Sphere into the the SphereStruct
		for (auto& tSpellsMapElem : this->m_SpellsList)
		{
			if (tSpellsMapElem.Value.MagicSphereType == SphereStructure.MagicSphereType)
			{
					SphereStructure.Spells.Add(tSpellsMapElem.Value);
			}

		}
		m_MagicSpheres.Add(SphereStructure.MagicSphereType, SphereStructure);
	}
}

bool USpellBookComponent::LoadSpellStructFromCompleteClass(FSpellStruct& TargetSpellStruct)
{
	if (!TargetSpellStruct.SpellClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s spell with ID '%i' cannot be spawned. It is set to use complete Spell Class. Please provide a complete Spell Class or set bUseCompleteSpellClass to false if the Spell should be customised directly in SpellBook."), *TargetSpellStruct.SpellName.ToString(), TargetSpellStruct.SpellID);
		return false;
	}
	TargetSpellStruct = TargetSpellStruct.SpellClass.GetDefaultObject()->m_SpellStruct;
	return true;
}

void USpellBookComponent::ClearCustomAbilities(FSpellStruct& TargetSpellStruct)
{
	//TargetSpellStruct.Abilities_AOE.Empty();
	//TargetSpellStruct.Abilities_Self.Empty();
}

