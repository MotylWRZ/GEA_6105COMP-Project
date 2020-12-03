// Fill out your copyright notice in the Description page of Project Settings.


#include "Particles/ParticleSystemComponent.h"

#include "Abilities/Ability_Self.h"




AAbility_Self::AAbility_Self()
	
{
	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));

	m_ParticleSystem->SetupAttachment(this->RootComponent);

	// Tests Only // Tests Only // Tests Only// Tests Only// Tests Only
	m_ParticleSystem->SetActive(true);
	m_ParticleSystem->SecondsBeforeInactive = 3.0f;
}

void AAbility_Self::BeginPlay()
{
	Super::BeginPlay();
}

void AAbility_Self::Initialise(AActor* AbilityUser)
{
	AAbility::Initialise(AbilityUser);
}

void AAbility_Self::UseAbility_Implementation()
{
	AAbility::UseAbility_Implementation();


	// Tests Only // Tests Only // Tests Only// Tests Only// Tests Only
	// Check if all have been used and the ability should be destroyed
	if (this->m_CurrentInterval < this->m_AbilityStructSelf.IntervalsNum)
	{
		this->m_CurrentInterval++;
	}
	else
	{
		this->SetIsAbilityActive(false);
		//this->AutoDestroy();
	}
}


