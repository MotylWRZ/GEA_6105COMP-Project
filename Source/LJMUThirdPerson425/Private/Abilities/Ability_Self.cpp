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
}

void AAbility_Self::UseAbility_Implementation()
{
	AAbility::UseAbility_Implementation();

	FTransform tUserTransform = this->m_AbilityUser->GetTransform();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->m_AbilityStructSelf.ParticleSystem, tUserTransform);

	this->m_bShouldUpdate = true;
}

void AAbility_Self::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	this->UpdateAbilityIntervals(this->m_AbilityStructSelf.AbilityIntervalStruct, DeltaTime);

	if (this->m_AbilityStructSelf.AbilityIntervalStruct.CurrentInterval >=
		this->m_AbilityStructSelf.AbilityIntervalStruct.IntervalsNum)
	{
		this->SetIsAbilityActive(false);
	}
}


