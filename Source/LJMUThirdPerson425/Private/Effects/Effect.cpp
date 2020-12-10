// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/ModifiersManager.h"

#include "Effects/Effect.h"

UEffect::UEffect()
	: m_AffectedActor(nullptr)
	, m_InstigatorActor(nullptr)
	, m_CurrentHitNum(0)
	, m_CurrentDuration(0.0f)
	, m_HitInterval(0.0f)
	, m_bIsActive(false)
	, m_bCanUseInstigatorStats(false)
	, m_CurrentHitInterval(0.0f)
{

}

bool UEffect::InitialiseEffect(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	if (!IsValid(InstigatorActor) || !IsValid(AffectedActor))
	{
		return false;
	}

	UActorStatsComponent* tInstigatorStatsComp = UActorStatsComponent::GetStatsComponent(InstigatorActor);

	if (tInstigatorStatsComp)
	{
		// Store instigator actor stats copy
		this->m_InstigatorActorStats = tInstigatorStatsComp->GetActorStatsStruct();
		this->m_bCanUseInstigatorStats = true;
	}

	this->m_InstigatorActor = InstigatorActor;
	this->m_AffectedActor = AffectedActor;
	this->m_EffectStruct = EffectStruct;
	this->m_HitInterval = this->m_EffectStruct.Duration / this->m_EffectStruct.HitsNum;

	this->SetIsActive(true);

	return true;

	this->OnEffectAdded.Broadcast(this);
}

void UEffect::Update(float DeltaTime)
{
	if (!this->m_bIsActive)
	{
		return;
	}

	// Calculate current duration
	this->m_CurrentDuration += DeltaTime;
	this->m_CurrentHitInterval += DeltaTime;



	if (this->m_CurrentDuration >= m_EffectStruct.Duration)
	{
		this->SetIsActive(false);
		this->m_CurrentDuration = 0.0f;
		return;
	}

	if (!m_EffectStruct.AllowMultiHit)
	{
		if (!this->m_bFirstEffectApplied)
		{
			this->ApplyEffect();
			this->m_bFirstEffectApplied = true;
		}
		return;
	}

	if (this->m_CurrentHitInterval < this->m_HitInterval)
	{
		return;
	}

	this->m_CurrentHitNum++;
	this->m_CurrentHitInterval = 0.0f;

	if (this->m_CurrentHitNum <= this->m_EffectStruct.HitsNum)
	{
		this->ApplyEffect();
	}
}

void UEffect::ApplyEffect()
{
	if (!this->m_AffectedActor)
	{
		// There is no AffectedActor availbale
		// Remove this effect
		this->SetIsActive(false);
		return;
	}

	if (!this->m_InstigatorActor)
	{
		// Check if the InstigatorStats can be used to to continue and keep this effect active
		// If we cannot use ActorStats, this effect will be removed
		if (!this->m_bCanUseInstigatorStats)
		{
			this->SetIsActive(false);
			return;
		}

		// Use InstigatorActorStats to continue applying this effect on AffectedActor
		if (UModifiersManager::ModifyActorStats(this->m_InstigatorActorStats, this->m_AffectedActor, this->m_EffectStruct.StatsModifierStruct))
		{
			this->OnEffectApplied.Broadcast(this);
		}
		return;
	}

	if (UModifiersManager::ModifyActorStats(this->m_InstigatorActor, this->m_AffectedActor, this->m_EffectStruct.StatsModifierStruct))
	{
		this->OnEffectApplied.Broadcast(this);
	}
}

float UEffect::GetEffectStatsScore()
{
	int32 tHitsLeft = this->m_EffectStruct.HitsNum - this->m_CurrentHitNum;
	float tDurationLeft = this->GetDurationLeft();
	int32 tDamage = this->m_EffectStruct.StatsModifierStruct.DamageToApply;
	int32 tHealth = this->m_EffectStruct.StatsModifierStruct.HealthToAdd;

	float tResult = static_cast<float>(tHitsLeft) + tDurationLeft + static_cast<float>(tDamage) + static_cast<float>(tHealth);

	return tResult;
}
