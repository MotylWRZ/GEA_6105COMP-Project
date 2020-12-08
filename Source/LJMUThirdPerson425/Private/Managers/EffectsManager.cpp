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



	UE_LOG(LogTemp, Error, TEXT("%i"), this->m_EffectsMap.Num());

	for (auto& tPair : this->m_EffectsMap)
	{
		// Go to the next iteration if the array is empty
		if (tPair.Value.Num() == 0)
		{
			continue;
		}

		for (auto& tEffect : tPair.Value)
		{
			tEffect->Update(DeltaTime);
		}

		// Remove all inactive Effects pointers from the Active array by predicate
		tPair.Value.RemoveAll([](UEffect* Effect)
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
		this->SetShouldUpdate(false);
	}
}

void UEffectsManager::Clear()
{
	Super::Clear();

	// Sort map elements based on the values(arrays) sizes
	this->m_EffectsMap.ValueSort([](TArray<UEffect*> tEffectsArrA, TArray<UEffect*> tEffectsArrB)
		{
			return tEffectsArrA.Num() < tEffectsArrB.Num();
		});

	for (TMap<AActor*, TArray<UEffect*>>::TIterator it = this->m_EffectsMap.CreateIterator(); it; ++it)
	{
		// If array if effects is empty, remove the element from the map
		if (it.Value().Num() == 0)
		{
			it.RemoveCurrent();
		}
	}
	// Gropud invalid elements together in order to prepare them for removal
	this->m_EffectsMap.Compact();
	// Remove invalid elements
	this->m_EffectsMap.Shrink();

}


void UEffectsManager::AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	// Create a new instance of tEffect locally
	UEffect* tEffect = NewObject<UEffect>();
	tEffect->InitialiseEffect(InstigatorActor, AffectedActor, EffectStruct);
	this->SetShouldUpdate(true);

	if (this->IsActorAffected(AffectedActor))
	{
		// If this actor is already affected, add the effect to the actor effects list
		this->m_EffectsMap.Find(AffectedActor)->Add(tEffect);
	}
	else
	{
		// Else, add new element to the map and add the effect to the new actor effects list
		TArray<UEffect*> tEffectsArray;
		tEffectsArray.Add(tEffect);

		this->m_EffectsMap.Add(AffectedActor, tEffectsArray);
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
	TArray<UEffect*>* tEffectsArray = this->m_EffectsMap.Find(AffectedActor);

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
	 return this->m_EffectsMap.Find(AffectedActor);

}

bool UEffectsManager::IsActorAffected(AActor* Actor)
{
	// Check if actor's memory address is stored as a key in the EffectsMap
	// If it is, it means that actor has at least one effect active
	return this->m_EffectsMap.Contains(Actor);
}
