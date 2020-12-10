// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/EffectsManager.h"

UEffectsManager::UEffectsManager()
{
	this->SetShouldUpdate(true);
	this->SetClearInterval(10.0f);
	this->SetUpdateInterval(0.1f);

}

void UEffectsManager::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	for (auto& tPair : this->m_EffectsMap)
	{
		// Go to the next iteration if the array is empty
		if (tPair.Value.EffectsArray.Num() == 0)
		{
			continue;
		}

		// Update all the effects from the current pair
		for (auto& tEffect : tPair.Value.EffectsArray)
		{
			if (tEffect)
			{
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

	// Temporary arry to store keys of inactive pairs (incative pair will be if the effects array is empty)
	TArray<AActor*> tInactiveElemKeys;

	for (TMap<AActor*, FEffectsArray>::TIterator it = this->m_EffectsMap.CreateIterator(); it; ++it)
	{
		// End the loop if value (array) is not empty. That means we reached the part of the map with filled Effect arrays
		if (it.Value().EffectsArray.Num() > 0)
		{
			break;
		}

		// Add the key of the element wit empty effects array
		tInactiveElemKeys.Add(it.Key());

	}

	// Clear the map from the elements with empty arrays
	for (int32 i = 0; i < tInactiveElemKeys.Num(); ++i)
	{
		this->m_EffectsMap.Remove(tInactiveElemKeys[i]);
	}

	// Gropud invalid elements together in order to prepare them for removal
	this->m_EffectsMap.Compact();
	// Remove invalid elements
	this->m_EffectsMap.Shrink();

}


void UEffectsManager::AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	if (!IsValid(InstigatorActor) || !IsValid(AffectedActor))
	{
		return;
	}

	// Create a new instance of tEffect locally
	UEffect* tEffect = NewObject<UEffect>();
	if (!tEffect->InitialiseEffect(InstigatorActor, AffectedActor, EffectStruct))
	{
		// Effect initialisation failed
		return;
	}
	this->SetShouldUpdate(true);

	if (this->IsActorAffected(AffectedActor))
	{
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

bool UEffectsManager::IsActorAffected(AActor* Actor)
{
	// Check if actor's memory address is stored as a key in the EffectsMap
	// If it is, it means that actor has at least one effect active
	return this->m_EffectsMap.Contains(Actor);
}
