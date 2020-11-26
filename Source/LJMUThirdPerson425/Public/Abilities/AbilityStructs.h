// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "AbilityStructs.generated.h"



class AAbility_Self;
class AAbility_AOE;
class AAbility;

// Ability Struct - Area Of Effect. It will affect the targets within the given radious.
USTRUCT(Blueprintable)
struct FAbilityStruct_AOE : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_AOE> AbilityAOEClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HealthToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RadiousStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bChangeRadiousDynamically;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bChangeRadiousDynamically"))
		float RadiousEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bChangeRadiousDynamically"))
		float ChangeDuration;



};

// Ability Struct - Self. The Ablility will directly affect the user of this ability(an Actor).
USTRUCT(Blueprintable)
struct FAbilityStruct_Self : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_Self> AbilitySelfClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HealthToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DamageToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseIntervals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float IntervalDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 IntervalsNum;

};