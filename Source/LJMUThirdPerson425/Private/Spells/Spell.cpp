// Fill out your copyright notice in the Description page of Project Settings.




#include "Abilities/Ability_Self.h"
#include "Abilities/Ability_AOE.h"

#include "Spells/Spell.h"


// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	this->RootComponent = m_RootComponent;

}

void ASpell::CastSpell(AActor* CasterRef)
{
	this->m_Caster = CasterRef;

	UseAbilities();
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
}

void ASpell::UseAbilities()
{
	/*for (auto& tAbilityClass : this->m_SpellStruct.Abilities)
	{
		AAbility* tNewAbility = CreateAbility(tAbilityClass);
		UseAbility(tNewAbility);
	}*/

	for (auto& tAbility : this->m_SpellStruct.Abilities_AOE)
	{
		AAbility_AOE* tNew = Cast<AAbility_AOE>(CreateAbility(tAbility.AbilityAOEClass));

		tNew->m_AOEAbilityStruct = tAbility;

		UseAbility(tNew);
	}

	for (auto& tAbility : this->m_SpellStruct.Abilities_Self)
	{
		AAbility_Self* tNew = Cast<AAbility_Self>(CreateAbility(tAbility.AbilitySelfClass));

		tNew->m_AbilityStructSelf = tAbility;

		UseAbility(tNew);
	}

	// Destroy Spell if there are no Active abilities
	if (this->m_ActiveSpells.Num() == 0)
	{
		this->AutoDestroy();
	}
}

void ASpell::AutoDestroy()
{
	this->Destroy();
}

void ASpell::ClearInActiveAbility(AAbility* InActiveAbility)
{
	this->m_ActiveSpells.Remove(InActiveAbility);

	// Check if there are any active spells
	if (this->m_ActiveSpells.Num() <= 0)
	{
		// If not, destroy the spell
		this->AutoDestroy();
	}
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAbility* ASpell::CreateAbility(TSubclassOf<AAbility> AbilityClass)
{
	AAbility* tNewAbility = GetWorld()->SpawnActor<AAbility>(AbilityClass, this->GetActorLocation(),
		this->GetActorRotation());

	if (tNewAbility)
	{
		return tNewAbility;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Create Ability !"));
		return nullptr;
	}

}

void ASpell::UseAbility(AAbility* Ability)
{
	if (Ability)
	{
		Ability->OnAbilityDestroyed.BindUObject(this, &ASpell::ClearInActiveAbility);

		Ability->Initialise(this->m_Caster);

		Ability->UseAbility();

		// Add recently used Ability to Active Spells map
		this->m_ActiveSpells.Emplace(Ability);
	}
}
