// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SelectableActorComponent.h"
#include "Components/CharacterStatsComponent.h"
#include "Components/CharacterCombatComponent.h"

#include "Characters/AICharacters/AICharacterBase.h"

AAICharacterBase::AAICharacterBase()
{
	this->m_SelectableActorComponent = CreateDefaultSubobject<USelectableActorComponent>(TEXT("SelectableActorComponent"));
	this->m_CharacterCombatComponent = CreateDefaultSubobject<UCharacterCombatComponent>(TEXT("CharacterCombatComponent"));
}

void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacterBase::ApplyDamage_Implementation(AActor* InstigatorActor, int32 DamageToApply)
{
	this->m_CharaterStatsComponent->TakeDamage(InstigatorActor, DamageToApply);
}

bool AAICharacterBase::IsAlive_Implementation()
{
	return this->m_CharaterStatsComponent->IsAlive();
}

bool AAICharacterBase::CanEffectBeApplied_Implementation(EEffectType EffectType)
{
	switch (EffectType)
	{
	case EEffectType::Effect_ArmorBuff:
	{
		return true;
	}
	case EEffectType::Effect_ArmorDebuff:
	{
		return true;
	}
	case EEffectType::Effect_Burning:
	{
		return true;
	}
	case EEffectType::Effect_Freezing:
	{
		return true;
	}
	case EEffectType::Effect_Healing:
	{
		return true;
	}
	case EEffectType::Effect_Poison:
	{
		return true;
	}
	}
	return true;
}
