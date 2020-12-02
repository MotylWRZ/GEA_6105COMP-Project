// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CombatComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Abilities/Ability_Targeted.h"

AAbility_Targeted::AAbility_Targeted()
	: m_TargetActor(nullptr)
{

}

void AAbility_Targeted::BeginPlay()
{
	Super::BeginPlay();
}

void AAbility_Targeted::Initialise(AActor* AbilityUser)
{
	Super::Initialise(AbilityUser);
}

void AAbility_Targeted::UseAbility()
{
	Super::UseAbility();
}

void AAbility_Targeted::UseAbility_Implementation()
{
	Super::UseAbility_Implementation();

	// Check if Ability user has combat component
	UCombatComponent* tUserCombatComp = UCombatComponent::GetCombatComponent(this->GetAbilityUser());

	if (!tUserCombatComp)
	{
		this->SetIsAbilityActive(false);
		return;
	}

	// Try to get a target from CombatComponent
	this->m_TargetActor = tUserCombatComp->GetCurrentTarget();

	if (!this->m_TargetActor)
	{
		this->SetIsAbilityActive(false);
		return;
	}

	this->m_ParticleSystem->Activate(true);
}
