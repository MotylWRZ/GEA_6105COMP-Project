// Fill out your copyright notice in the Description page of Project Settings.



#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "Abilities/Ability_Self.h"




AAbility_Self::AAbility_Self()

{
}

void AAbility_Self::BeginPlay()
{
	Super::BeginPlay();
}

void AAbility_Self::Initialise(AActor* AbilityUser)
{
	AAbility::Initialise(AbilityUser);

	// Setup base Class Properties
	this->SetupAbilityBase(this->m_AbilityStructSelf);
}

void AAbility_Self::UseAbility_Implementation()
{
	AAbility::UseAbility_Implementation();

	FTransform tUserTransform = this->m_AbilityUser->GetTransform();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->m_AbilityStructSelf.ParticleSystem, tUserTransform);
	//// Tests Only // Tests Only // Tests Only// Tests Only// Tests Only
	//// Check if all have been used and the ability should be destroyed
	//if (this->m_CurrentInterval < this->m_AbilityStructSelf.IntervalsNum)
	//{
	//	this->m_CurrentInterval++;
	//}
	//else
	//{
	//	this->SetIsAbilityActive(false);
	//	//this->AutoDestroy();
	//}
}


