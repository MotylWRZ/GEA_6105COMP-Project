// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/CanHasEffectsInterface.h"
#include "Utilities/General/HelperFunctionsLibrary.h"

#include "Managers/EffectsManager.h"

UEffectsManager::UEffectsManager()
{
	this->SetShouldUpdate(true);
	this->SetClearInterval(5.0f);
	this->SetUpdateInterval(0.1f);

}

void UEffectsManager::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	for (auto& tPair : this->m_EffectsMap)
	{
		// Go to the next iteration if the array is empty
		if (tPair.Value.EffectsArray.Num() == 0 || !tPair.Key->GetClass()->IsValidLowLevel())
		{
			continue;
		}


		for (int32 i = 0; i < tPair.Value.EffectsArray.Num(); ++i)
		{
			UEffect* tEffect = tPair.Value.EffectsArray[i];

			if (tEffect->GetClass()->IsValidLowLevel())
			{
				FEffectStruct tStruct = tEffect->GetEffectStruct();

				tEffect->Update(DeltaTime);
			}
		}

		// Remove all inactive Effects pointers from the Active array by predicate
		tPair.Value.EffectsArray.RemoveAll([](UEffect* Effect)
		{
				return !Effect->IsActive();
		});
	}

	if(this->ShouldClear())
	{
		this->Clear();
	}

	if (this->m_EffectsMap.Num() == 0)
	{
		this->m_EffectsMap.Empty(0);
		this->SetShouldUpdate(false);
	}
}

void UEffectsManager::Clear()
{
	Super::Clear();

	// Do not attempt to clear the map if it is empty
	if (this->m_EffectsMap.Num() == 0)
	{
		return;
	}

	// Sort map elements based on the values(arrays) sizes
	// Elements with empty arrays will be at the beginning of the structure
	this->m_EffectsMap.ValueSort([](FEffectsArray tEffectsArrA, FEffectsArray tEffectsArrB)
		{
			return tEffectsArrA.EffectsArray.Num() < tEffectsArrB.EffectsArray.Num();
		});

	for (TMap<AActor*, FEffectsArray>::TIterator it = this->m_EffectsMap.CreateIterator(); it; ++it)
	{
		// End the loop if value (array) is not empty. That means we reached the part of the map with filled Effect arrays
		if (it.Value().EffectsArray.Num() > 0)
		{
			break;
		}

		// Clear the empty element
		this->m_EffectsMap.Remove(it.Key());

	}

	// Gropud invalid elements together in order to prepare them for removal
	this->m_EffectsMap.Compact();
	// Remove invalid elements
	this->m_EffectsMap.Shrink();

}

UEffect* UEffectsManager::CreateEffectFromStruct(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	UEffect* tNewEffect;

	if (EffectStruct.UsePremadeEffectClass && EffectStruct.EffectClass)
	{
		// Create an Effect of specified, premade class
		tNewEffect = NewObject<UEffect>(this->GetWorld(), EffectStruct.EffectClass);
		if (EffectStruct.OverwriteEffectClassProperties)
		{
			// Initialise effect and overwrite the default class struct from the specified class
			tNewEffect->InitialiseEffect(InstigatorActor, AffectedActor, EffectStruct);
		}
		else
		{
			// Initialise effect and load the default class struct from the specified class
			tNewEffect->InitialiseEffect(InstigatorActor, AffectedActor, EffectStruct.EffectClass.GetDefaultObject()->GetEffectStruct());
		}
	}
	else
	{
		// Create and initialise default Effect object
		tNewEffect = NewObject<UEffect>(this->GetWorld());
		tNewEffect->InitialiseEffect(InstigatorActor, AffectedActor, EffectStruct);
	}

	// Check if effect can be applied on allies and enemies
	if (!tNewEffect || (!tNewEffect->GetEffectStruct().ApplyEffectOnAllies && !UActorStatsComponent::IsEnemyByActor(InstigatorActor, AffectedActor))
		|| (!tNewEffect->GetEffectStruct().ApplyEffectOnEnemies && UActorStatsComponent::IsEnemyByActor(InstigatorActor, AffectedActor)))
	{
		return nullptr;
	}
	else
	{
		// Return the created effect
		return tNewEffect;
	}
}


void UEffectsManager::AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	if (!IsValid(InstigatorActor) || !IsValid(AffectedActor) || !UHelperFunctionsLibrary::CanActorHasEffects(AffectedActor))
	{
		return;
	}

	// Check if affected actor is alive
	UActorStatsComponent* tAffectedActorStats = UActorStatsComponent::GetStatsComponent(AffectedActor);
	if(tAffectedActorStats && !tAffectedActorStats->IsAlive())
	{
		return;
	}

	// Return if the AffectedActor cannot take the effect of the current type
	if (!ICanHasEffectsInterface::Execute_CanEffectBeApplied(AffectedActor, EffectStruct.EffectType))
	{
		return;
	}

	bool a = UActorStatsComponent::IsEnemyByActor(InstigatorActor, AffectedActor);



	// Create a new instance of tEffect locally
	UEffect* tEffect = this->CreateEffectFromStruct(InstigatorActor, AffectedActor, EffectStruct);

	if (!tEffect)
	{
		return;
	}

	this->SetShouldUpdate(true);

	if (this->IsActorAffected(AffectedActor))
	{
		// Try to find and replace the active effect with the same type
		if (this->AddAndReplaceEffect(tEffect, AffectedActor))
		{
			// If found and replaced, do not continue
			return;
		}

		//If this actor is already affected, add the effect to the actor effects list
		this->m_EffectsMap.Find(AffectedActor)->EffectsArray.Add(tEffect);
	}
	else
	{
		// Else, add new element to the map and add the effect to the new actor effects list
		TArray<UEffect*> tEffectsArray;
		tEffectsArray.Add(tEffect);

		FEffectsArray tArrayStruct;
		tArrayStruct.EffectsArray = tEffectsArray;

		this->m_EffectsMap.Add(AffectedActor, tArrayStruct);
		//this->m_EffectsMap.Add(AffectedActor, tEffectsArray);
	}

}

void UEffectsManager::AddEffectsToActor(AActor* InstigatorActor, AActor* AffectedActor, const TArray<FEffectStruct>& EffectsStructs)
{
	for (auto tEffectStruct : EffectsStructs)
	{
		this->AddEffectToActor(InstigatorActor, AffectedActor, tEffectStruct);
	}
}

void UEffectsManager::FindEffectsByActor(AActor* AffectedActor, TArray<UEffect*>& EffectsArray, bool& IsArrayFound)
{
	TArray<UEffect*>* tEffectsArray = &this->m_EffectsMap.Find(AffectedActor)->EffectsArray;

	if (!tEffectsArray)
	{
		IsArrayFound = false;
		return;
	}

	EffectsArray = *tEffectsArray;
	IsArrayFound = true;

}

const TArray<UEffect*>* UEffectsManager::GetEffectsByActor(AActor* AffectedActor) const
{
	// Returns nullptr if the key can't be found
	 return &this->m_EffectsMap.Find(AffectedActor)->EffectsArray;

}

bool UEffectsManager::AddAndReplaceEffect(UEffect* EffectToAdd, AActor* AffectedActor)
{
	UEffect* tEffectCurrent;

	tEffectCurrent = this->GetEffectAlreadyAppliedByType(EffectToAdd->GetEffectStruct().EffectType, AffectedActor);

	// Return false if tEffectCurrent is null
	// This means that it cannot be found in the effects array
	if (!tEffectCurrent)
	{
		return false;
	}

	// Compare the StatsScore of these two effects
	UEffect* tHigherScoreEffect = this->GetEffectWithHigherStatsScore(tEffectCurrent, EffectToAdd);

	if (tHigherScoreEffect == EffectToAdd || !tEffectCurrent->IsActive())
	{
		// Remove Current Effect
		// Set this effect to inactive so that it will be removed from the array
		tEffectCurrent->SetIsActive(false);
		//this->m_EffectsMap.Find(AffectedActor)->EffectsArray.Remove(tEffectCurrent);

		// Add EffectToAdd as it has better score
		this->m_EffectsMap.Find(AffectedActor)->EffectsArray.Add(tHigherScoreEffect);

		return true;
	}
	else
	{
		return false;
	}

}

UEffect* UEffectsManager::GetEffectWithHigherStatsScore(UEffect* EffectA, UEffect* EffectB)
{

	if (!EffectA || !EffectB)
	{
		return nullptr;
	}

	//Check the StatsScore
	float tScoreA = EffectA->GetEffectStatsScore();
	float tScoreB = EffectB->GetEffectStatsScore();

	if (tScoreA >= tScoreB)
	{
		return EffectA;
	}
	else
	{
		return EffectB;
	}
}

UEffect* UEffectsManager::GetEffectAlreadyAppliedByType(EEffectType EffectType, AActor* AffectedActor)
{
	// try to find the effect with same type as EffectToAdd
	for (auto& tEffect : *this->GetEffectsByActor(AffectedActor))
	{
		if (tEffect->GetEffectStruct().EffectType == EffectType)
		{
			return tEffect;
		}
	}

	return nullptr;
}

bool UEffectsManager::IsActorAffected(AActor* Actor)
{

	// Check if actor's memory address is stored as a key in the EffectsMap
	// If it is, it means that actor has at least one effect active
	return this->m_EffectsMap.Contains(Actor);
}
