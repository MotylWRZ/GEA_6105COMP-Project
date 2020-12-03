// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "AbilityStructs.generated.h"


class AAbility_Targeted;
class AAbility_Self;
class AAbility_AOE;
class AAbility;



USTRUCT()
struct FAbilityStruct : public FTableRowBase
{
	GENERATED_BODY()

	explicit FAbilityStruct();

	// Particle system that will be used for this ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;

	// Amount of damage this ability will apply to its targets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	// Amount of health this ability will add to its targets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthToAdd;

	// Allow this ability to take effect more than once  (i.e restart itself)?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseIntervals;

	// Duration between the next auto use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UseIntervals", EditConditionHides))
	float IntervalDuration;

	// Number of intervals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UseIntervals", EditConditionHides))
	int32 IntervalsNum;
};

// Ability Struct - Area Of Effect. It will affect the targets within the given radious.
USTRUCT(Blueprintable)
struct FAbilityStruct_AOE : public FAbilityStruct
{
	GENERATED_BODY()

		explicit FAbilityStruct_AOE();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_AOE> AbilityAOEClass;
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
struct FAbilityStruct_Self : public FAbilityStruct
{
	GENERATED_BODY()

		explicit FAbilityStruct_Self();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_Self> AbilitySelfClass;
};

// Ability Struct - Self. The Ablility will directly affect the user of this ability(an Actor).
USTRUCT(Blueprintable)
struct FAbilityStruct_Targeted : public FAbilityStruct
{
	GENERATED_BODY()

		explicit FAbilityStruct_Targeted();

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_Targeted> AbilityTargetedClass;
};


UENUM(BlueprintType)enum class EAbilityType : uint8
{
	Ability_Targeted,
	Ability_Self,
	Ability_AOE,
};

USTRUCT()
struct FAbilityStructCustomised : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = "CustomisedAbility")
	EAbilityType AbilityType = EAbilityType::Ability_Self;

	UPROPERTY(EditAnywhere, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_Targeted", EditConditionHides))
		FAbilityStruct_Targeted AbilityTargetedStruct;
	UPROPERTY(EditAnywhere, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_Self", EditConditionHides))
		FAbilityStruct_Self AbilitySelfStruct;
	UPROPERTY(EditAnywhere, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_AOE", EditConditionHides))
		FAbilityStruct_AOE AbilityAOEStruct;
};