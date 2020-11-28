// Fill out your copyright notice in the Description page of Project Settings.

#include "../../LJMUThirdPerson425.h"
#include "Components/ActorStatsComponent.h"
#include "Interfaces/AttackableInterface.h"
#include "Abilities/Ability.h"



// Sets default values
AAbility::AAbility()
	:m_AbilityUser(nullptr)
	, m_bInitialised(false)
	, m_bIsAbilityActive(true)
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

void AAbility::ApplyDamageToActor(AActor* Actor, int32 DamageToApply)
{
	if (!Actor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass()))
	{
		return;
	}

	// Apply damage to Actor
	IAttackableInterface::Execute_ApplyDamage(Actor, this->m_AbilityUser, DamageToApply);
}

void AAbility::AddHealthToActor(AActor* Actor, int32 HealthToAdd)
{
	if (!Actor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass()))
	{
		return;
	}

	// Try to get a Stats Component from the Actor
	UActorStatsComponent* tStatsComponent = UActorStatsComponent::GetStatsComponent(Actor);

	if (tStatsComponent)
	{
		tStatsComponent->AddHealth(this->m_AbilityUser, HealthToAdd);
	}
}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
}

