// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"

#include "Components/ActorStatsComponent.h"




// Sets default values for this component's properties
UActorStatsComponent::UActorStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UActorStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorStatsComponent::ModifyHealth(int32 ModifyingValue)
{
	if (!this->m_CanBeDamaged && ModifyingValue < 0)
	{
		return;
	}

	int32 OldHealth = this->m_Health;
	int32 NewHealth = FMath::Clamp(this->m_Health + ModifyingValue, 0, this->m_HealthMax);

	int32 Delta = NewHealth - OldHealth;

	this->m_Health = NewHealth;

	if (Delta != 0)
	{
		// MulticastHealthChanged
		if (Delta > 0)
		{
			// MulticastOnHealed
			this->OnActorHealed.Broadcast();
		}
		else
		{
			// MulticastOnDamaged
			this->OnActorDamaged.Broadcast();
		}
	}

	if (Delta < 0 && !this->IsAlive())
	{
		// MulticastOnDestroyed
		this->OnActorDestroyed.Broadcast();
	}
}

void UActorStatsComponent::ModifyMaxHealth(int32 ModifyingValue)
{
	int32 OldHealthMax = this->m_HealthMax;
	int32 NewHealthMax = this->m_HealthMax + ModifyingValue;

	if (this->m_Health > NewHealthMax)
	{
		this->m_Health = FMath::Clamp(this->m_Health, 0, NewHealthMax);
	}

	this->m_HealthMax = NewHealthMax;
}

void UActorStatsComponent::TakeDamage(UPARAM(ref) AActor*& InstigatorActor, int32 DamageToApply)
{
	// Try to get a StatsComponentn from the Instigator Actor
	UActorStatsComponent* tInstigatorStats = UActorStatsComponent::GetStatsComponent(InstigatorActor);

	// Check if the ComponentStats is valid and compare the team Ids in order to identify enemy/ally
	// Apply damage to enemies only
	if (tInstigatorStats && !IsEnemyByComponent(tInstigatorStats, this))
	{
		return;
	}
	ModifyHealth(-DamageToApply);
}

void UActorStatsComponent::AddHealth(UPARAM(ref) AActor*& InstigatorActor, int32 HealthToAdd)
{
	UActorStatsComponent* tInstigatorStats = UActorStatsComponent::GetStatsComponent(InstigatorActor);

	// Check if the ComponentStats is valid and compare the team Ids in order to identify enemy/ally
	// Add health to allies only
	if (tInstigatorStats && IsEnemyByComponent(tInstigatorStats, this))
	{
		return;
	}
	ModifyHealth(HealthToAdd);
}

UActorStatsComponent* UActorStatsComponent::GetStatsComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UActorStatsComponent>(FromActor->GetComponentByClass(UActorStatsComponent::StaticClass()));
	}
	return nullptr;
}

bool UActorStatsComponent::IsEnemyByActor(AActor* Actor1, AActor* Actor2)
{
	UActorStatsComponent* tActor1Stats = UActorStatsComponent::GetStatsComponent(Actor1);
	UActorStatsComponent* tActor2Stats = UActorStatsComponent::GetStatsComponent(Actor2);

	return UActorStatsComponent::IsEnemyByComponent(tActor1Stats, tActor2Stats);
}

bool UActorStatsComponent::IsEnemyByComponent(UActorStatsComponent* StatsComponent1, UActorStatsComponent* StatsComponent2)
{
	if (!StatsComponent1 || !StatsComponent2 || StatsComponent1->GetTeamID() == StatsComponent2->GetTeamID())
	{
		return false;
	}
	return true;
}


