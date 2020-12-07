// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Managers/ModifiersManager.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectsStructs.generated.h"


UENUM(BlueprintType)enum class EEffectType : uint8
{
	Effect_Healing,
	Effect_Poison,
	Effect_Burning,
	Effect_Freezing,
	Effect_SpeedBuff,
	Effect_SpeedDebuff,
	Effect_AttackBuff,
	Effect_AttackDebuff,
	Effect_ArmorBuff,
	Effect_ArmorDebuff
};

USTRUCT(Blueprintable)
struct FEffectStruct : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEffectType EffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStatsModifierStruct StatsModifierStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName EffectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EffectDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AllowIntervals = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 IntervalsNum = 1;


};

//USTRUCT()
//struct FEffectConstructionStruct
//{
//	GENERATED_BODY()
//
//		UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		FStatsModifierStruct StatsModifierStruct;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		float Duration = 1.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		bool AllowIntervals = false;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 IntervalsNum = 1;
//
//
//};