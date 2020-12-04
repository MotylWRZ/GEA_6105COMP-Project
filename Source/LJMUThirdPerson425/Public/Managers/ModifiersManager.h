// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CharacterStatsComponent.h"
#include "Components/CombatComponent.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "ModifiersManager.generated.h"



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
	int32 DamageToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanDamageAllies;
};


UCLASS()
class LJMUTHIRDPERSON425_API AModifiersManager : public AManagerBase
{
	GENERATED_BODY()

public:
	AModifiersManager();
	static void ModifyActorStats(AActor* InstigatorActor, AActor* ActorToModify, const FStatsModifierStruct& StatsModifierStruct);

};
