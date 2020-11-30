// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"

#include "Components/ActorStatsComponent.h"
#include "Abilities/Ability_AOE.h"


AAbility_AOE::AAbility_AOE()
{
	// Sphere Collision Component setup

	this->m_SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));

	this->m_SphereCollisionComponent->SetupAttachment(this->RootComponent);

	this->m_bShouldUpdate = true;
	this->m_DesiredUpdateInterval = 1.1f;
}

void AAbility_AOE::BeginPlay()
{
	Super::BeginPlay();
}

void AAbility_AOE::Initialise(AActor* AbilityUser)
{
	Super::Initialise(AbilityUser);

	this->m_SphereCollisionComponent->SetSphereRadius(this->m_AOEAbilityStruct.RadiousStart);

	// If Radious won't be changed dynamically, set the end radious equal to the start radious
	if (!this->m_AOEAbilityStruct.bChangeRadiousDynamically)
	{
		this->m_AOEAbilityStruct.RadiousEnd = this->m_AOEAbilityStruct.RadiousStart;
	}
}

void AAbility_AOE::UseAbility_Implementation()
{
	Super::UseAbility_Implementation();
	// Check all the overlapping Actors and apply damage to those that are Attackable
	TArray<AActor*> tActors;

	this->m_SphereCollisionComponent->GetOverlappingActors(tActors, TSubclassOf<AActor>());

	for (auto& tActor : tActors)
	{
		// Add Health and apply damage to the actors
		AddHealthToActor(tActor, this->m_AOEAbilityStruct.HealthToAdd);
		ApplyDamageToActor(tActor, this->m_AOEAbilityStruct.Damage);
	}

	// Destroy the spell once the Collision sphere reaches its End value
	// Or if it is set to not change the radious dynamically
	if (this->m_SphereCollisionComponent->GetUnscaledSphereRadius() >= this->m_AOEAbilityStruct.RadiousEnd ||
		!this->m_AOEAbilityStruct.bChangeRadiousDynamically)
	{
		this->SetIsAbilityActive(false);
	}
}

void AAbility_AOE::UpdateSphereCollision(float DeltaTime)
{
	float tStep = (this->m_AOEAbilityStruct.RadiousEnd - this->m_AOEAbilityStruct.RadiousStart) / this->m_AOEAbilityStruct.ChangeDuration * DeltaTime;

	float tTargetRadious = this->m_SphereCollisionComponent->GetUnscaledSphereRadius() + tStep;

	this->m_SphereCollisionComponent->SetSphereRadius(tTargetRadious);
}

void AAbility_AOE::ApplyDamageToActor(AActor* Actor, int32 DamageToApply)
{
	// Apply damage and add this actor to the AffectedActors array if it is not in there already
	if (!this->m_AffectedActors.Contains(Actor))
	{
		Super::ApplyDamageToActor(Actor, DamageToApply);
		this->m_AffectedActors.AddUnique(Actor);
	}
}

void AAbility_AOE::AddHealthToActor(AActor* Actor, int32 HealthToAdd)
{
	// Add health and add this actor to the AffectedActors array if it is not in there already
	/*if (!this->m_AffectedActors.Contains(Actor))
	{
		Super::AddHealthToActor(Actor, HealthToAdd);
		this->m_AffectedActors.AddUnique(Actor);
	}*/
}

void AAbility_AOE::Update(float DeltaTime)
{
	AAbility::Update(DeltaTime);

	this->UseAbility();
	UpdateSphereCollision(DeltaTime);
}
