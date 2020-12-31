// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Managers/ModifiersManager.h"
#include "Effects/EffectsStructs.h"



#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "AbilityStructs.generated.h"

class AAbility_Targeted;
class AAbility_Self;
class AAbility_AOE;
class AAbility;
class USoundCue;

USTRUCT(Blueprintable)
struct FAbilityIntervalStruct
{
	GENERATED_BODY()

		// Interval setup properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool	UseIntervals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	IntervalDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	IntervalsNum;

	// Editable interval values
	int32	CurrentInterval;
	float	CurrentIntervalTime;
};


USTRUCT(Blueprintable)
struct FAbilityStruct : public FTableRowBase
{
	GENERATED_BODY()

	explicit FAbilityStruct();

	public:

	// Particle system that will be used for this ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* AbilitySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatsModifierStruct StatsModifierStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEffectStruct> Effects;


};

// Ability Struct - Area Of Effect. It will affect the targets within the given radious.
USTRUCT(Blueprintable)
struct FAbilityStruct_AOE : public FAbilityStruct
{
	GENERATED_BODY()

		explicit FAbilityStruct_AOE();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAbility_AOE> AbilityAOEClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float RadiousStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bChangeRadiousDynamically;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bChangeRadiousDynamically", ClampMin = "0"))
		float RadiousEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bChangeRadiousDynamically", ClampMin = "0"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityIntervalStruct AbilityIntervalStruct;
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

USTRUCT(Blueprintable)
struct FAbilityStructCustomised
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "CustomisedAbility")
	EAbilityType AbilityType = EAbilityType::Ability_Self;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_Targeted", EditConditionHides))
		FAbilityStruct_Targeted AbilityTargetedStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_Self", EditConditionHides))
		FAbilityStruct_Self AbilitySelfStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomisedAbility", meta = (EditCondition = "AbilityType == EAbilityType::Ability_AOE", EditConditionHides))
		FAbilityStruct_AOE AbilityAOEStruct;
};