// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/WorldSettings.h"
#include "Components/ActorStatsComponent.h"
#include "Interfaces/AttackableInterface.h"
#include "Utilities/Animation/AnimationHelpers.h"

#include "Components/CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
	: m_TargetActor(nullptr)
	, m_AnimatedMesh(nullptr)
	, m_ComponentUpdateInterval(0.1f)
	, m_MeleeAttackRange(300.0f)
	, m_MeleeAttackIntervalDuration(3.0f)
	, m_MeleeAttackDamage(10)
	, m_RangedAttackRange(500.0f)
	, m_RangedAttackIntervalDuration(3.0f)
	, m_RangedAttackDamage(10)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();


	// Set CurrentTime to CurrentMode attack interval value in order to perform the initial Attack action immidiately
	if (this->m_CurrentAttackMode = EAttackMode::Attack_Melee)
	{
		m_CurrentTime = this->m_MeleeAttackIntervalDuration;
	}
	else
	{
		m_CurrentTime = this->m_RangedAttackIntervalDuration;
	}

	// Access the World Settings
	// Activate the timer
	GetWorld()->GetTimerManager().SetTimer(this->m_CombatTimerHandle, this,
		&UCombatComponent::CustomTickComponent, this->m_ComponentUpdateInterval,
		true);

	// Pause the timer
	GetWorld()->GetTimerManager().PauseTimer(this->m_CombatTimerHandle);

}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::CustomTickComponent()
{
	// Return if there is no active target
	if (!this->m_TargetActor)
	{
		return;
	}

	// Decide whether the Melee or Ranged attack should be performed
	if (this->CanAttackMelee())
	{
		this->SetAttackMode(EAttackMode::Attack_Melee);
	}
	else if (this->CanAttackRanged())
	{
		this->SetAttackMode(EAttackMode::Attack_Ranged);
	}
	else
	{
		this->ResetAttack();
		return;
	}

	// Initiate attack action
	this->AttackStart();
}

void UCombatComponent::AttackStart()
{
	// Update Current Time
	this->m_CurrentTime += GetWorld()->GetTimerManager().GetTimerElapsed(this->m_CombatTimerHandle);


	// Play AnimMontage based on the curent AttackMode
	switch (this->m_CurrentAttackMode)
	{
	case EAttackMode::Attack_Melee:
	{
		// If CurrentTimer is lower than the MeleeAttackSpeed, do not continue
		if (this->m_MeleeAttackIntervalDuration > this->m_CurrentTime)
		{
			return;
		}
		UAnimationHelpers::PlayMontageRandomlyWithLength(this->m_MeleeAnimationMontage,
														 this->m_AnimatedMesh,
														 this->m_MeleeAttackIntervalDuration);
		break;
	}
	case EAttackMode::Attack_Ranged:
	{
		// If CurrentTimer is lower than the RangedAttackSpeed, do not continue
		if (this->m_RangedAttackIntervalDuration > this->m_CurrentTime)
		{
			return;
		}
		UAnimationHelpers::PlayMontageRandomlyWithLength(this->m_RangedAnimationMontage,
														 this->m_AnimatedMesh,
														 this->m_RangedAttackIntervalDuration);
		break;
	}
	}

	// Return if target is not alive or is not valid
	if (!this->m_TargetActor || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	{
		this->ResetAttack();
		return;
	}

	// Change the IsAttacking flag to true
	this->m_IsAttacking = true;

	// Reset CurrentTime and continue Attack
	this->m_CurrentTime = 0.0f;

	this->OnAttackStart.Broadcast();
}

void UCombatComponent::PerformAttack()
{
	this->OnAttack.Broadcast();

	// Perform the Attack action based on the current AttackMode
	switch (this->m_CurrentAttackMode)
	{
	case EAttackMode::Attack_Melee:
	{
		this->PerformMeleeAttack();
		break;
	}
	case EAttackMode::Attack_Ranged:
	{
		this->PerformRangedAttack();
		break;
	}
	}
}

void UCombatComponent::PerformMeleeAttack()
{
	this->OnAttackMelee.Broadcast();

	AActor* tOwner = this->GetOwner();

	if (!this->m_TargetActor || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	{
		return;
	}

	IAttackableInterface::Execute_ApplyDamage(this->m_TargetActor, tOwner, this->m_MeleeAttackDamage);
}

void UCombatComponent::PerformRangedAttack()
{
	this->OnAttackRanged.Broadcast();

	if (!this->m_bInstantEffectRanged || !this->m_TargetActor || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	{
		return;
	}

	AActor* tOwner = this->GetOwner();

	IAttackableInterface::Execute_ApplyDamage(this->m_TargetActor, tOwner, this->m_RangedAttackDamage);
}

void UCombatComponent::SetTarget(AActor* NewTarget)
{
	// Set a new Target. Return if it is NULL or does not implement StatsInterface
	if (!NewTarget || !NewTarget->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass()))
	{
		this->m_TargetActor = nullptr;
		this->ResetAttack();
		return;
	}

	// If not alive, reset TargetActor and return
	if (!IAttackableInterface::Execute_IsAlive(NewTarget))
	{
		this->m_TargetActor = nullptr;
		this->ResetAttack();
		return;
	}

	// If it is alive set it as a new target
	this->m_TargetActor = NewTarget;

	// UnPause the Timer
	GetWorld()->GetTimerManager().UnPauseTimer(this->m_CombatTimerHandle);
}

void UCombatComponent::ResetAttack()
{
	if (!this->m_IsAttacking)
	{
		return;
	}

	// Stop All montages
	this->m_AnimatedMesh->GetAnimInstance()->StopAllMontages(0.3f);

	// Set CurrentTime to CurrentMode attack interval value in order to perform the initial Attack action immidiately
	if (this->m_CurrentAttackMode = EAttackMode::Attack_Melee)
	{
		m_CurrentTime = this->m_MeleeAttackIntervalDuration;
	}
	else
	{
		m_CurrentTime = this->m_RangedAttackIntervalDuration;
	}


	this->m_IsAttacking = false;

	this->m_TargetActor = nullptr;

	// Pause the timer
	GetWorld()->GetTimerManager().PauseTimer(this->m_CombatTimerHandle);

	this->OnReturnToIdle.Broadcast();
}

bool UCombatComponent::CanAttackRanged()
{
	if (this->IsTargetInRangedRange() && this->m_bIsRangedActive)
	{
		return true;
	}
	return false;
}

bool UCombatComponent::CanAttackMelee()
{
	if (this->IsTargetInMeleeRange() && this->m_bIsMeleeActive)
	{
		return true;
	}
	return false;
}

bool UCombatComponent::IsTargetInMeleeRange()
{
	float tDistance = this->GetDistanceToTarget();

	if (tDistance < this->m_MeleeAttackRange)
	{
		return true;
	}

	return false;
}

bool UCombatComponent::IsTargetInRangedRange()
{
	float tDistance = this->GetDistanceToTarget();

	if (tDistance < this->m_RangedAttackRange)
	{
		return true;
	}

	return false;
}

float UCombatComponent::GetDistanceToTarget()
{
	// Return false if there is no active target
	if (!this->m_TargetActor)
	{
		return false;
	}

	AActor* tOwner = this->GetOwner();

	FVector tOwnerLoc = tOwner->GetActorLocation();
	FVector tTargetLoc = this->m_TargetActor->GetTargetLocation();

	// Calculate the distance between the target and the owner
	const float tDistance = FVector::Dist(tOwnerLoc, tTargetLoc);

	return tDistance;
}



