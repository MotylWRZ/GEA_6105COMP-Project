// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AbilitiesManager.h"

AAbilitiesManager::AAbilitiesManager()
{
}

void AAbilitiesManager::Update()
{
	AManagerBase::Update();
	// Update all spells

	for (int32 i = 0; i < this->m_ActiveAbilities.Num(); i++)
	{
		AAbility* tAbility = this->m_ActiveAbilities[i];

		tAbility->Update(this->GetWorld()->GetTimerManager().GetTimerElapsed(this->m_ManagerTimerHandle));

		if (!tAbility->IsAbilityActive())
		{
			this->m_InactiveAbilities.Add(tAbility);
		}
	}

	// Remove all inactive Ability pointers from the Active array
	m_ActiveAbilities.RemoveAll([](AAbility* Ability)
		{
			return !Ability->IsAbilityActive();
		});


	if (this->ShouldClear())
	{
		// Clear the the inactive abilitoes array and destroy inactive Ability intances
		this->Clear();
	}

	if (this->m_ActiveAbilities.Num() == 0 && this->m_InactiveAbilities.Num() == 0)
	{
		// Stop updating this manager
		this->SetShouldUpdate(false);

		// Reset Update interval to Default value
		this->ResetUpdateInterval();
	}
}

void AAbilitiesManager::Clear()
{
	Super::Clear();

	for (int32 i = 0; i < this->m_InactiveAbilities.Num(); i++)
	{
		this->m_InactiveAbilities[i]->AutoDestroy();
	}
	m_InactiveAbilities.Empty();
}

AAbility* AAbilitiesManager::CreateAbility(TSubclassOf<AAbility> AbilityClass, AActor* AbilityUser)
{
	FTransform tUserTransform = AbilityUser->GetTransform();

	AAbility* tNewAbility = GetWorld()->SpawnActor<AAbility>(AbilityClass, tUserTransform);

	if (tNewAbility)
	{
		tNewAbility->Initialise(AbilityUser);
		this->m_ActiveAbilities.Add(tNewAbility);
		this->SetShouldUpdate(true);

		// Adjust the manager update interval to the ability desired interval
		if (this->GetUpdateInterval() > tNewAbility->GetDesiredUpdateInterval())
		{
			this->SetUpdateInterval(tNewAbility->GetDesiredUpdateInterval());
		}

		return tNewAbility;
	}


		UE_LOG(LogTemp, Error, TEXT("Cannot Create Ability !"));
		return nullptr;
}

//AAbility* AAbilitiesManager::CreateAbilityFromStruct(FAbilityStruct* AbilityStruct, AActor* AbilityUser)
//{
//	FAbilityStruct_AOE tStructAOE = *static_cast<FAbilityStruct_AOE*>(AbilityStruct);
//	FAbilityStruct_Self tStructSelf = *static_cast<FAbilityStruct_Self*>(AbilityStruct);
//	return nullptr;
//}
