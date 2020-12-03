// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CharacterStatsComponent.h"
#include "Components/CombatComponent.h"
#include "Components/SpellBookComponent.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "ModifiersManager.generated.h"

USTRUCT(Blueprintable)
struct FStatsModifierStruct
{
	GENERATED_BODY()

	FCombatStruct CombatModifier;

};

UCLASS()
class LJMUTHIRDPERSON425_API AModifiersManager : public AManagerBase
{
	GENERATED_BODY()

	void ModifyActorStats(AActor* ActorToModify, FStatsModifierStruct StatsModifierStruct);

};
