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
	if (!this->m_ActorStats.CanBeDamaged && ModifyingValue < 0)
	{
		return;
	}

	int32 OldHealth = this->m_ActorStats.Health;
	int32 NewHealth = FMath::Clamp(this->m_ActorStats.Health + ModifyingValue, 0, this->m_ActorStats.HealthMax);

	int32 Delta = NewHealth - OldHealth;

	this->m_ActorStats.Health = NewHealth;

	if (Delta != 0)
	{
		OnActorHealthModified.Broadcast();
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

	if (!this->IsAlive())
	{
		// MulticastOnDestroyed
		this->OnActorKilled.Broadcast();
	}
}

void UActorStatsComponent::ModifyMaxHealth(int32 ModifyingValue)
{
	int32 OldHealthMax = this->m_ActorStats.HealthMax;
	int32 NewHealthMax = this->m_ActorStats.HealthMax + ModifyingValue;

	if (this->m_ActorStats.Health > NewHealthMax)
	{
		this->m_ActorStats.Health = FMath::Clamp(this->m_ActorStats.Health, 0, NewHealthMax);
	}

	OnActorHealthModified.Broadcast();

	this->m_ActorStats.HealthMax = NewHealthMax;
}

void UActorStatsComponent::TakeDamage(UPARAM(ref) AActor*& InstigatorActor, int32 DamageToApply)
{
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
	if (!Actor1 || !Actor2)
	{
		return false;
	}

	UActorStatsComponent* tActor1Stats = UActorStatsComponent::GetStatsComponent(Actor1);
	UActorStatsComponent* tActor2Stats = UActorStatsComponent::GetStatsComponent(Actor2);

	return UActorStatsComponent::IsEnemyByComponent(tActor1Stats, tActor2Stats);
}

bool UActorStatsComponent::IsEnemyByComponent(UActorStatsComponent* StatsComponentA, UActorStatsComponent* StatsComponentB)
{
	if (!StatsComponentA || !StatsComponentB || StatsComponentA->GetTeamID() == StatsComponentB->GetTeamID())
	{
		return false;
	}
	return true;
}

bool UActorStatsComponent::IsEnemyByStatsStruct(const FActorStatsStruct& StatsStructA, const FActorStatsStruct& StatsStructB)
{
	if (StatsStructA.TeamID == StatsStructB.TeamID)
	{
		return false;
	}
	return true;
}


