// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/ModifiersManager.h"

#include "Effects/Effect.h"

UEffect::UEffect(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	, m_AffectedActor(nullptr)
	, m_InstigatorActor(nullptr)
	, m_CurrentHitNum(0)
	, m_CurrentDuration(0.0f)
	, m_HitInterval(0.0f)
	, m_IsActive(false)
{

}

void UEffect::InitialiseEffect(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	this->m_InstigatorActor = InstigatorActor;
	this->m_AffectedActor = AffectedActor;
	this->m_EffectStruct = EffectStruct;
	this->m_HitInterval = this->m_EffectStruct.Duration / this->m_EffectStruct.HitsNum;

	this->SetIsActive(true);

	this->OnEffectAdded.Broadcast(this);
}

void UEffect::Update(float DeltaTime)
{
	if (!this->m_IsActive)
	{
		return;
	}

	// Calculate current duration
	this->m_CurrentDuration += DeltaTime;

	if (this->m_CurrentDuration >= m_EffectStruct.Duration)
	{
		this->SetIsActive(false);
		this->OnEffectRemoved.Broadcast(this);
		this->m_CurrentDuration = 0.0f;
		return;
	}

	if (!m_EffectStruct.AllowMultiHit)
	{
		this->ApplyEffect();
		return;
	}

	this->m_CurrentHitNum++;

	if (this->m_CurrentHitNum <= this->m_EffectStruct.HitsNum)
	{
		this->ApplyEffect();
	}
}

void UEffect::ApplyEffect()
{
	if (UModifiersManager::ModifyActorStats(this->m_InstigatorActor, this->m_AffectedActor, this->m_EffectStruct.StatsModifierStruct))
	{
		this->OnEffectApplied.Broadcast(this);
	}
}
