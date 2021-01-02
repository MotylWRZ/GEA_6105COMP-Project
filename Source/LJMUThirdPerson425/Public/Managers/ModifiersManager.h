// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CharacterStatsComponent.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "ModifiersManager.generated.h"

class USpellBookComponent;

USTRUCT(Blueprintable)
//Use this struct to Modify any property of the target actor
struct FStatsFullModifierStruct
{
	GENERATED_BODY()

		/*FCombatStruct CombatModifier;
		FActorStatsStruct ActorStatsStruct;*/

};

USTRUCT(Blueprintable)
// Use this struct to Modify ONLY main properties of the target actor
struct FStatsModifierStruct
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FCombatStruct CombatModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DamageToApply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthToAdd = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ModifySpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ModifyArmor = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ModifyMana = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanDamageAllies = false;

	// Overloading "+" operator in order to allow StatsStructs addition
	FStatsModifierStruct operator+(const FStatsModifierStruct& Other);

	// Overloading "-" operator in order to allow StatsStructs subtraction
	FStatsModifierStruct operator-(const FStatsModifierStruct& Other);
};


UCLASS()
class LJMUTHIRDPERSON425_API UModifiersManager : public UManagerBase
{
	GENERATED_BODY()

public:
	UModifiersManager();

	// Checks whether the ActorToModify IsAttackable (has implemented this interface)
	// Then it will attempt to retrieve the actor stats component
	// After a check wheter the target actor is an ally or enemiy in realtion to Instigator actor, the stats will be modified
	static bool ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct);

	// This version of ModifyActorStats function allows to use InstigatorActorStats struct instead of pointer to actor.
	// This can allow to store InstigatorActorStats(a copy of it) and use it to modify other actor even if Instigator actor has been destroyed
	static bool ModifyActorStats(const FActorStatsStruct& InstigatorActorStats, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct);

	// Checks whether the ActorToModify IsAttackable (has implemented this interface)
	// Then it will attempt to retrieve the actor stats component
	// After a check wheter the target actor is an ally or enemy in relation to Instigator actor, the stats will be modified
	// Only basic stats can be modified using this function and they have to be explicitly specified
	static bool ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, int32 DamageToApply = 0, int32 HealthToAdd = 0, bool CanDamageAllies = false);

protected:
	static void ModifyActorStatsComponent(AActor* InstigatorActor, UActorStatsComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct);
	static void ModifyActorCharacterComponent(AActor* InstigatorActor, UCharacterStatsComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct);
	static void ModifyActorSpellbookComponent(AActor* InstigatorActor, USpellBookComponent* ComponentToModify, const FStatsModifierStruct& StatsModifierStruct);
};
