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

		explicit FAbilityStruct() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAbility> AbilityClasss;
};

// Ability Struct - Area Of Effect. It will affect the targets within the given radious.
USTRUCT(Blueprintable)
struct FAbilityStruct_AOE : public FAbilityStruct
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
struct FAbilityStruct_Self : public FAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_Self> AbilitySelfClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HealthToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DamageToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseIntervals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float IntervalDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 IntervalsNum;

};

// Ability Struct - Self. The Ablility will directly affect the user of this ability(an Actor).
USTRUCT(Blueprintable)
struct FAbilityStruct_Targeted : public FAbilityStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_Targeted> AbilityTargetedClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HealthToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DamageToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseIntervals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float IntervalDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 IntervalsNum;
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

	FAbilityStruct* AbilityStruct;
};