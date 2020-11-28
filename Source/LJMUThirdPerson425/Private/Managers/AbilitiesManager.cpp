// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AbilitiesManager.h"

AAbilitiesManager::AAbilitiesManager()
{

}

void AAbilitiesManager::Update()
{
	AManagerBase::Update();
	// Update all spells
	for (int32 i = this->m_ActiveAbilities.Num() - 1; i >= 0; --i)
	{
		AAbility* tAbility = m_ActiveAbilities[i];

		if (!tAbility->IsAbilityActive())
		{
			// Destroy and clear inactive spell
			this->m_ActiveAbilities.RemoveSwap(tAbility);

			if (!tAbility)
			{
				return;
			}

			tAbility->AutoDestroy();
		}
	}

	if (this->m_ActiveAbilities.Num() == 0)
	{
		// Stop updating this manager
		this->SetShouldUpdate(false);
	}
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
		return tNewAbility;
	}


		UE_LOG(LogTemp, Error, TEXT("Cannot Create Ability !"));
		return nullptr;
}
