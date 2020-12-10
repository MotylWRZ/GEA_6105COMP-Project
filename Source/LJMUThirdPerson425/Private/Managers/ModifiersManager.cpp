// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/General/HelperFunctionsLibrary.h"
#include "Interfaces/AttackableInterface.h"

#include "Managers/ModifiersManager.h"



UModifiersManager::UModifiersManager()
{

}

bool UModifiersManager::ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	if (!IsValid(InstigatorActor) || !IsValid(ActorToModify))
	{
		return false;
	}

	// Modify Actor Stats
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(ActorToModify);

	if (!tStatsComponent || !UHelperFunctionsLibrary::IsActorAttackable(ActorToModify))
	{
		return false;
	}

	// Check if these actors are enemies for each other
	if (!UActorStatsComponent::IsEnemyByActor(InstigatorActor, ActorToModify))
	{
		// If they are allies add health
		tStatsComponent->AddHealth(InstigatorActor, StatsModifierStruct.HealthToAdd);

		// Apply damage to ally only if it is allowed
		if (StatsModifierStruct.CanDamageAllies)
		{
			IAttackableInterface::Execute_ApplyDamage(ActorToModify, InstigatorActor, StatsModifierStruct.DamageToApply);
		}
		return true;
	}

	// Apply damage to enemy actor
	IAttackableInterface::Execute_ApplyDamage(ActorToModify, InstigatorActor, StatsModifierStruct.DamageToApply);

	return true;

}

bool UModifiersManager::ModifyActorStats(const FActorStatsStruct& InstigatorActorStats, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	// Modify Actor Stats
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(ActorToModify);

	if (!tStatsComponent || !UHelperFunctionsLibrary::IsActorAttackable(ActorToModify))
	{
		return false;
	}

	return false;
}

bool UModifiersManager::ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, int32 DamageToApply, int32 HealthToAdd, bool CanDamageAllies)
{
	if (!InstigatorActor || !ActorToModify)
	{
		return false;
	}

	// Modify Actor Stats
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(ActorToModify);

	if (!tStatsComponent || !UHelperFunctionsLibrary::IsActorAttackable(ActorToModify))
	{
		return false;
	}

	// Check if these actors are enemies for each other
	if (!UActorStatsComponent::IsEnemyByActor(InstigatorActor, ActorToModify))
	{
		// If they are allies add health
		tStatsComponent->AddHealth(InstigatorActor, HealthToAdd);

		// Apply damage to ally only if it is allowed
		if (CanDamageAllies)
		{
			IAttackableInterface::Execute_ApplyDamage(ActorToModify, InstigatorActor, DamageToApply);
		}
		return true;
	}

	// Apply damage to enemy actor
	IAttackableInterface::Execute_ApplyDamage(ActorToModify, InstigatorActor, DamageToApply);

	return true;
}

FStatsModifierStruct FStatsModifierStruct::operator+(const FStatsModifierStruct& Other)
{
	FStatsModifierStruct tStatsModifier;

	tStatsModifier.DamageToApply = this->DamageToApply + Other.DamageToApply;
	tStatsModifier.HealthToAdd = this->HealthToAdd + Other.HealthToAdd;

	return tStatsModifier;
}

FStatsModifierStruct FStatsModifierStruct::operator-(const FStatsModifierStruct& Other)
{
	FStatsModifierStruct tStatsModifier;

	tStatsModifier.DamageToApply = this->DamageToApply - Other.DamageToApply;
	tStatsModifier.HealthToAdd = this->HealthToAdd - Other.HealthToAdd;

	return tStatsModifier;
}
