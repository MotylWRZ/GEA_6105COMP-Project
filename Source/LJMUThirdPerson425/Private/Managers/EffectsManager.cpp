// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/EffectsManager.h"

void UEffectsManager::AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, FEffectStruct& EffectStruct)
{
	FEffectStruct tEffectStruct = EffectStruct;

	if (this->IsActorAffected(AffectedActor))
	{
		// If this actor is already affected, add the effect to the actor effects list
		this->m_EffectsMap.Find(AffectedActor)->Add(tEffectStruct);
	}
	else
	{
		// Else, add new element to the map and add the effect to the new actor effects list
		TArray<FEffectStruct> tStructsArray;
		tStructsArray.Add(tEffectStruct);

		this->m_EffectsMap.Add(AffectedActor, tStructsArray);
	}


}

bool UEffectsManager::IsActorAffected(AActor* Actor)
{
	// Check if actor's memory address is stored as a key in the EffectsMap
	// If it is, it means that actor has at least one effect active
	return this->m_EffectsMap.Contains(Actor);
}
