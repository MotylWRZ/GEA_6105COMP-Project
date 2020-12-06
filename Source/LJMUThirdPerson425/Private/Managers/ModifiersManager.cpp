// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/General/HelperFunctionsLibrary.h"

#include "Managers/ModifiersManager.h"



UModifiersManager::UModifiersManager()
{

}

bool UModifiersManager::ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	// Modify Actor Stats
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(ActorToModify);

	if (!tStatsComponent || !UHelperFunctionsLibrary::IsActorAttackable(ActorToModify))
	{
		return false;
	}

	int32 tActorTeam = tStatsComponent->GetTeamID();

	// Check if these actors are enemies for each other
	if (!UActorStatsComponent::IsEnemyByActor(InstigatorActor, ActorToModify))
	{
		// If they are allies add health
		tStatsComponent->AddHealth(InstigatorActor, StatsModifierStruct.HealthToAdd);

		// Apply damage to ally only if it is allowed
		if (StatsModifierStruct.CanDamageAllies)
		{
			tStatsComponent->TakeDamage(InstigatorActor, StatsModifierStruct.DamageToApply);
		}
		return true;
	}

	// Apply damage to enemy actor
	tStatsComponent->TakeDamage(InstigatorActor, StatsModifierStruct.DamageToApply);

	return true;

}
