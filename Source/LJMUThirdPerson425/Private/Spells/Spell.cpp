// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/RPGGameInstance.h"
#include "Managers/AbilitiesManager.h"


#include "Spells/Spell.h"


// Sets default values
ASpell::ASpell()
	:m_bIsActive(true)
	, m_Caster(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	this->RootComponent = m_RootComponent;

}

bool ASpell::CastSpell(AActor* CasterRef)
{
	this->m_Caster = CasterRef;

	// Check if the spell should be casted based on its SuccessChance
	if (this->ShouldCast())
	{
		UseAbilities();
		return true;
	}
	this->m_bIsActive = false;
	return false;
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();


}

void ASpell::UseAbilities()
{
	UAbilitiesManager* tAbilitiesManager = URPGGameInstance::GetAbilitiesManager(this);
	AAbility* tNewAbility;
	for (auto& tAbilityClass : this->m_SpellStruct.Abilities)
	{
		tNewAbility = tAbilitiesManager->SpawnAbility(tAbilityClass, this->m_Caster);
		UseAbility(tNewAbility);
	}

	if (this->m_SpellStruct.bCustomiseAbilities)
	{
		for (auto& tAbilityCustomisedStruct : this->m_SpellStruct.CustomisedAbilities)
		{
			tNewAbility = tAbilitiesManager->SpawnCustomisedAbilityFromStruct(&tAbilityCustomisedStruct, this->m_Caster);
			UseAbility(tNewAbility);
		}
	}

	// Destroy Spell if there are no Active abilities
	if (this->m_ActiveAbilities.Num() == 0)
	{
		// Mark the spell as inactive so that it can be destroyed
		this->m_bIsActive = false;
		//this->AutoDestroy();
	}
}

void ASpell::AutoDestroy()
{
	this->Destroy();
}

void ASpell::ClearInActiveAbility(AAbility* InActiveAbility)
{
	this->m_ActiveAbilities.Remove(InActiveAbility);

	// Check if there are any active abilities
	if (this->m_ActiveAbilities.Num() <= 0)
	{
		// If not, mark the spell as inactive
		this->m_bIsActive = false;
	}
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell::UseAbility(AAbility* Ability)
{
	if (Ability)
	{
		Ability->OnAbilityDestroyed.BindUObject(this, &ASpell::ClearInActiveAbility);

		Ability->UseAbility();

		// Add recently used Ability to Active Spells map
		this->m_ActiveAbilities.Emplace(Ability);
	}
}
