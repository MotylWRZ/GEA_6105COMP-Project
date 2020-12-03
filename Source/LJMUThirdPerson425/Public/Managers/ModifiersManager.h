// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CharacterStatsComponent.h"
#include "Components/CombatComponent.h"
#include "Components/SpellBookComponent.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "ModifiersManager.generated.h"

USTRUCT(Blueprintable)
// Use this struct to Modify any property of the target actor
struct FStatsFullModifierStruct
{
	GENERATED_BODY()

	FCombatStruct CombatModifier;
	FActorStatsStruct ActorStatsStruct;

};

USTRUCT(Blueprintable)
// Use this struct to Modify ONLY main properties of the target actor
struct FStatsModifierStruct
{
	GENERATED_BODY()

	FCombatStruct CombatModifier;
	int32 DamageToApply;
	int32 HealthToAdd;

	bool CanDamageAllies;
};


UCLASS()
class LJMUTHIRDPERSON425_API AModifiersManager : public AManagerBase
{
	GENERATED_BODY()

public:
	AModifiersManager();
	void ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, FStatsModifierStruct StatsModifierStruct);
	
};
