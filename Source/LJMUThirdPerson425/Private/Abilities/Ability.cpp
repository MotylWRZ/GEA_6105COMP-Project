// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/EffectsManager.h"
#include "Managers/ModifiersManager.h"
#include "../../LJMUThirdPerson425.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameInstances/RPGGameInstance.h"

#include "Utilities/General/HelperFunctionsLibrary.h"
#include "Components/ActorStatsComponent.h"
#include "Interfaces/AttackableInterface.h"


#include "Abilities/Ability.h"



// Sets default values
AAbility::AAbility()
	:m_AbilityUser(nullptr)
	, m_bInitialised(false)
	, m_bShouldUpdate(false)
	, m_bIsAbilityActive(true)
	, m_DesiredUpdateInterval(0.1f)
	, m_CurrentUpdateTime(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	this->RootComponent = m_RootComponent;
}

void AAbility::UseAbility_Implementation()
{
	if (!this->m_bInitialised)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s can't be used, because it is not Initialised."), *this->GetName());
		this->AutoDestroy();
		return;
	}
	this->SetActorTransform(this->m_AbilityUser->GetTransform());



}

void AAbility::Initialise(AActor* AbilityUser)
{
	// Set the Ability User
	m_AbilityUser = AbilityUser;

	if (!m_AbilityUser)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s cannot be Initialised. Ability User is NULL."), *this->GetName());
		return;
	}

	// If everyhting has been set properly, set m_bInitialised to TRUE
	this->m_bInitialised = true;
}

void AAbility::AutoDestroy()
{
	// Clear the ability timers
	this->GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	// Call the delegate. Let the listeners know that this ability is being destroyed.
	this->OnAbilityDestroyed.Execute(this);
	this->Destroy();
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();


}

void AAbility::SetDesiredUpdateInterval(float NewDesiredUpdateInterval)
{
	this->m_DesiredUpdateInterval = NewDesiredUpdateInterval;
}

void AAbility::ApplyStatsModifierToActor(AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct)
{
	UModifiersManager::ModifyActorStats(this->m_AbilityUser, ActorToModify, StatsModifierStruct);
}

void AAbility::Update(float DeltaTime)
{
	// return if there is no need to update the ability
	if (!this->m_bShouldUpdate)
	{
		this->m_bIsAbilityActive = false;
		return;
	}

	// Ability Update Interval

	this->m_CurrentUpdateTime += DeltaTime;

	if (this->m_CurrentUpdateTime < this->m_DesiredUpdateInterval)
	{
		return;
	}

	this->m_CurrentUpdateTime = 0.0f;
}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
}

void AAbility::UpdateAbilityIntervals(FAbilityIntervalStruct& AbilityIntervalStruct, float DeltaTime)
{
	if (!AbilityIntervalStruct.UseIntervals)
	{
		return;
	}

	// Calculate the Interval time
	AbilityIntervalStruct.CurrentIntervalTime += DeltaTime;

	if (AbilityIntervalStruct.IntervalDuration > AbilityIntervalStruct.CurrentIntervalTime)
	{
		return;
	}

	// Check if all intervals have been used
	if (AbilityIntervalStruct.CurrentInterval <= AbilityIntervalStruct.IntervalsNum)
	{
		// Restart the Ability
		this->UseAbility();
		AbilityIntervalStruct.CurrentIntervalTime = 0.0f;
		AbilityIntervalStruct.CurrentInterval++;
		return;
	}

	AbilityIntervalStruct.UseIntervals = false;

}

void AAbility::ApplyEffectOnActor(AActor* AffectedActor, const FEffectStruct& EffectStruct)
{
	UEffectsManager* tEffectsManager = URPGGameInstance::GetEffectsManager(this);

	tEffectsManager->AddEffectToActor(this->m_AbilityUser, AffectedActor, EffectStruct);
}

void AAbility::ApplyEffectsonActor(AActor* AffectedActor, const TArray<FEffectStruct>& EffectsStructs)
{
	UEffectsManager* tEffectsManager = URPGGameInstance::GetEffectsManager(this);

	tEffectsManager->AddEffectsToActor(this->m_AbilityUser, AffectedActor, EffectsStructs);
}
