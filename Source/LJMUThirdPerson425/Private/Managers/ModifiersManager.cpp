// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpellbookComponent.h"

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

	// try to get the ActorStatsComponent from the ActorToModify
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(ActorToModify);

	if (tStatsComponent)
	{
		// Try to cast the ActorStatsComponent to the CharacterStatsComponent class
		UCharacterStatsComponent* tCharacterStatsComponent = Cast<UCharacterStatsComponent>(tStatsComponent);

		if (tCharacterStatsComponent)
		{
			// If cast succeeded
			// Modify the CharacterStatsComponent (this will modify basic ActorStats and Characater stats)
			ModifyActorCharacterComponent(InstigatorActor, tCharacterStatsComponent, StatsModifierStruct);
		}
		else
		{
			// If cast failed
			// Modify the ActorStatsComponent
			ModifyActorStatsComponent(InstigatorActor, tStatsComponent, StatsModifierStruct);
		}
	}

	// Try to get the Spellbook component from the ActorToModify
	USpellBookComponent* tSpellbookComponent = Cast<USpellBookComponent>(ActorToModify->GetComponentByClass(USpellBookComponent::StaticClass()));

	if (tSpellbookComponent)
	{
		// Modify the SpellbookComponent
		ModifyActorSpellbookComponent(InstigatorActor, tSpellbookComponent, StatsModifierStruct);
	}

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

void UModifiersManager::ModifyActorStatsComponent(AActor* InstigatorActor, UActorStatsComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	// Modify Actor Stats
	UActorStatsComponent* tStatsComponent = ComponentToModify;
	AActor* tComponentOwner = tStatsComponent->GetOwner();

	if (!tStatsComponent || !tComponentOwner)
	{
		return;
	}

	// Check if these actors are enemies for each other
	if (!UActorStatsComponent::IsEnemyByActor(InstigatorActor, tComponentOwner))
	{
		// If they are allies add health
		tStatsComponent->AddHealth(InstigatorActor, StatsModifierStruct.HealthToAdd);

		// Apply damage to ally only if it is allowed
		if (StatsModifierStruct.CanDamageAllies && UHelperFunctionsLibrary::IsActorAttackable(tComponentOwner))
		{

			IAttackableInterface::Execute_ApplyDamage(tComponentOwner, InstigatorActor, StatsModifierStruct.DamageToApply);
		}
		return;
	}

	if (UHelperFunctionsLibrary::IsActorAttackable(tComponentOwner))
	{
		// Apply damage to enemy actor
		IAttackableInterface::Execute_ApplyDamage(tComponentOwner, InstigatorActor, StatsModifierStruct.DamageToApply);
	}

}

void UModifiersManager::ModifyActorCharacterComponent(AActor* InstigatorActor, UCharacterStatsComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	UCharacterStatsComponent* tCharacterStatsComponent = ComponentToModify;

	if (!tCharacterStatsComponent)
	{
		return;
	}

	ModifyActorStatsComponent(InstigatorActor, ComponentToModify, StatsModifierStruct);

	tCharacterStatsComponent->ModifySpeed(StatsModifierStruct.ModifySpeed);
	tCharacterStatsComponent->ModifyArmor(StatsModifierStruct.ModifyArmor);
}

void UModifiersManager::ModifyActorSpellbookComponent(AActor* InstigatorActor, USpellBookComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	USpellBookComponent* tSpellbookComponent = ComponentToModify;

	if (!tSpellbookComponent)
	{
		return;
	}

	tSpellbookComponent->ModifyMana(StatsModifierStruct.ModifyMana);
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
