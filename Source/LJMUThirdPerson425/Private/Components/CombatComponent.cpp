// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Utilities/General/HelperFunctionsLibrary.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"

#include "Components/ActorStatsComponent.h"
#include "Interfaces/AttackableInterface.h"
#include "Utilities/Animation/AnimationHelpers.h"
#include "Projectiles/ProjectileBase.h"
#include "Managers/ModifiersManager.h"


#include "Components/CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
	: m_TargetActor(nullptr)
	, m_AnimatedMesh(nullptr)
	, m_ComponentUpdateInterval(0.1f)
	, m_CurrentAttackMode(EAttackMode::Attack_Melee)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Default Properties for Melee Combat
	this->m_MeleeCombatStruct.AttackRange = 300.0f;
	this->m_MeleeCombatStruct.AttackIntervalDuration = 3.0f;
	this->m_MeleeCombatStruct.AttackDamage = 10;

	// Default Properties for Ranged Combat
	this->m_RangedCombatStruct.AttackRange = 500.0f;
	this->m_RangedCombatStruct.AttackIntervalDuration = 3.0f;
	this->m_RangedCombatStruct.AttackDamage = 10;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();


	// Set CurrentTime to CurrentMode attack interval value in order to perform the initial Attack action immidiately
	if (this->m_CurrentAttackMode = EAttackMode::Attack_Melee)
	{
		m_CurrentTime = this->m_MeleeCombatStruct.AttackIntervalDuration;
	}
	else
	{
		m_CurrentTime = this->m_RangedCombatStruct.AttackIntervalDuration;
	}

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

	//// Return if target is not alive or is not valid
	//if (!this->m_TargetActor || !this->m_TargetActor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass()) || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	//{
	//	this->ResetAttack();
	//	return;
	//}


	// Play AnimMontage based on the curent AttackMode
	switch (this->m_CurrentAttackMode)
	{
	case EAttackMode::Attack_Melee:
	{
		// If CurrentTimer is lower than the MeleeAttackSpeed, do not continue
		if (this->m_MeleeCombatStruct.AttackIntervalDuration > this->m_CurrentTime)
		{
			return;
		}

		UAnimationHelpers::PlayMontageRandomlyWithLength(this->m_MeleeCombatStruct.AnimationMontage,
														 this->m_AnimatedMesh,
														 this->m_MeleeCombatStruct.AttackIntervalDuration);
		break;
	}
	case EAttackMode::Attack_Ranged:
	{
		// If CurrentTimer is lower than the RangedAttackSpeed, do not continue
		if (this->m_RangedCombatStruct.AttackIntervalDuration > this->m_CurrentTime)
		{
			return;
		}

		UAnimationHelpers::PlayMontageRandomlyWithLength(this->m_RangedCombatStruct.AnimationMontage,
														 this->m_AnimatedMesh,
														 this->m_RangedCombatStruct.AttackIntervalDuration);
		break;
	}
	}



	// Change the IsAttacking flag to true
	this->m_bIsAttacking = true;

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

	// Play Attack Sound
	this->PlayAttackSound();
}

void UCombatComponent::PerformMeleeAttack()
{
	this->OnAttackMelee.Broadcast();

	AActor* tOwner = this->GetOwner();

	if (!this->m_TargetActor || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	{
		return;
	}

	IAttackableInterface::Execute_ApplyDamage(this->m_TargetActor, tOwner, this->m_MeleeCombatStruct.AttackDamage);
}

void UCombatComponent::PerformRangedAttack()
{
	this->OnAttackRanged.Broadcast();


	if (this->m_RangedCombatStruct.UseProjectiles)
	{
		this->ShootProjectile();
		return;
	}

	if (!this->m_RangedCombatStruct.bInstantEffect || !this->m_TargetActor || !IAttackableInterface::Execute_IsAlive(this->m_TargetActor))
	{
		return;
	}

	AActor* tOwner = this->GetOwner();

	IAttackableInterface::Execute_ApplyDamage(this->m_TargetActor, tOwner, this->m_RangedCombatStruct.AttackDamage);
}

float UCombatComponent::GetTargetDistanceWithLineTrace()
{
	TArray<FHitResult> tHitResults;

	FVector tPosStart = this->GetOwner()->GetActorLocation();
	FVector tPosEnd = this->m_TargetActor->GetActorLocation();

	const FName TraceTag("MyTraceTag");

	FCollisionQueryParams tTraceParams;
	tTraceParams.TraceTag = TraceTag;

	//UKismetSystemLibrary::LineTrace(this, tPosStart, tPosEnd, ETraceTypeQuery::)
	GetWorld()->LineTraceMultiByChannel(tHitResults, tPosStart, tPosEnd, ECollisionChannel::ECC_Visibility, tTraceParams);

	for (auto& tHitResult : tHitResults)
	{
		AActor* tHitActor = tHitResult.Actor.Get();

		// Check if thitActor is the current TragetActor
		if (tHitActor == this->m_TargetActor)
		{
			// return line trace distance to the target
			return tHitResult.Distance;
		}
	}

	return 99999.0f;
}

void UCombatComponent::SetTarget(AActor* NewTarget)
{
	// Set a new Target. Return if it is NULL or does not implement AttackableInterface
	if (!NewTarget || !UHelperFunctionsLibrary::IsActorAttackable(NewTarget)
		|| !UActorStatsComponent::IsEnemyByActor(this->GetOwner(), NewTarget))
	{
		this->ResetAttack();
		return;
	}

	// If not alive, reset TargetActor and return
	if (!IAttackableInterface::Execute_IsAlive(NewTarget))
	{
		this->ResetAttack();
		return;
	}

	if (this->m_TargetActor == NewTarget)
	{
		return;
	}

	// If it is alive set it as a new target
	this->m_TargetActor = NewTarget;

	// UnPause the Timer
	GetWorld()->GetTimerManager().UnPauseTimer(this->m_CombatTimerHandle);
}

void UCombatComponent::ResetAttack()
{
	if (!this->m_bIsAttacking)
	{
		return;
	}

	// Stop All montages
	this->m_AnimatedMesh->GetAnimInstance()->StopAllMontages(0.3f);

	// Set CurrentTime to CurrentMode attack interval value in order to perform the initial Attack action immidiately
	if (this->m_CurrentAttackMode = EAttackMode::Attack_Melee)
	{
		m_CurrentTime = this->m_MeleeCombatStruct.AttackIntervalDuration;
	}
	else
	{
		m_CurrentTime = this->m_RangedCombatStruct.AttackIntervalDuration;
	}

	this->m_bIsAttacking = false;

	this->m_TargetActor = nullptr;

	// Pause the timer
	GetWorld()->GetTimerManager().PauseTimer(this->m_CombatTimerHandle);

	this->OnReturnToIdle.Broadcast();
}

void UCombatComponent::ShootProjectile()
{

	if (!this->m_RangedCombatStruct.ProjectileClass || !this->m_TargetActor)
	{
		return;
	}

	// Setup initial projectile transform

	// Calculate start projectile location as relative to the component owner's location
	FVector tStartLocation = this->m_RangedCombatStruct.ProjectileLaunchRelativeLocation + this->GetOwner()->GetActorLocation();
	FTransform tStartTransform = this->GetOwner()->GetTransform();
	tStartTransform.SetLocation(tStartLocation);

	FVector tTargetLocation = this->m_TargetActor->GetActorLocation();

	// Spawn projectile object
	AProjectileBase* tProjectile = GetWorld()->SpawnActor<AProjectileBase>(this->m_RangedCombatStruct.ProjectileClass, tStartTransform);

	// Create a temporary modifier stats struct
	FStatsModifierStruct tStatsModifierStruct;

	// Setup the StatsModifierStruct values. Assign the combat stats values to it
	tStatsModifierStruct.CanDamageAllies = false;
	tStatsModifierStruct.DamageToApply = this->m_RangedCombatStruct.AttackDamage;

	// Initialise the Projectile object
	tProjectile->Initialise(this->GetOwner(), &tStatsModifierStruct, &this->m_RangedCombatStruct.ProjectileStruct);

	// Adjust the projectile velocity, so that it will try to land at the target location
	tProjectile->AdjustProjectileVelocityToHitTarget(tTargetLocation);
}

void UCombatComponent::PlayAttackSound()
{
	FVector tOwnerLocation = this->GetOwner()->GetActorLocation();

	// Play the attack sound based on the current Attack Mode
	switch (this->m_CurrentAttackMode)
	{
	case EAttackMode::Attack_Melee:
	{
		if (this->m_MeleeCombatStruct.AttackSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), this->m_MeleeCombatStruct.AttackSound,
													tOwnerLocation);
		}
		break;
	}
	case EAttackMode::Attack_Ranged:
	{
		if (this->m_RangedCombatStruct.AttackSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), this->m_RangedCombatStruct.AttackSound, tOwnerLocation);
		}
		break;
	}
	default:
		break;
	}
}

bool UCombatComponent::CanAttackRanged()
{
	if (this->IsTargetInRangedRange()&& this->m_bIsRangedActive)
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

	if (tDistance < this->m_MeleeCombatStruct.AttackRange)
	{
		return true;
	}

	float tDistanceFromLineTrace = this->GetTargetDistanceWithLineTrace();

	if (tDistanceFromLineTrace <= this->m_MeleeCombatStruct.AttackRange)
	{
		return true;
	}

	return false;
}

bool UCombatComponent::IsTargetInRangedRange()
{
	float tDistance = this->GetDistanceToTarget();

	if (tDistance < this->m_RangedCombatStruct.AttackRange)
	{
		return true;
	}

	float tDistanceFromLineTrace = this->GetTargetDistanceWithLineTrace();

	if (tDistanceFromLineTrace <= this->m_RangedCombatStruct.AttackRange)
	{
		return true;
	}

	return false;
}

float UCombatComponent::GetDistanceToTarget()
{
	AActor* tOwner = this->GetOwner();

	// Return false if there is no active target
	if ((m_TargetActor && !m_TargetActor->GetClass()->IsValidLowLevel()) || !tOwner)
	{
		return false;
	}

	FVector tOwnerLoc = tOwner->GetActorLocation();
	FVector tTargetLoc = this->m_TargetActor->GetActorLocation();

	// Calculate the distance between the target and the owner
	const float tDistance = FVector::Dist(tOwnerLoc, tTargetLoc);

	return tDistance;
}

UCombatComponent* UCombatComponent::GetCombatComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UCombatComponent>(FromActor->GetComponentByClass(UCombatComponent::StaticClass()));
	}
	return nullptr;
}