// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Managers/ModifiersManager.h"

#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectsStructs.generated.h"

class UEffect;

UENUM(BlueprintType)enum class EEffectType : uint8
{
	Effect_Healing,
	Effect_Poison,
	Effect_Burning,
	Effect_Freezing,
	Effect_ArmorBuff,
	Effect_ArmorDebuff
};

USTRUCT(Blueprintable)
struct FEffectStruct : public FTableRowBase
{
	GENERATED_BODY()

	// Use one of premade effect classes.
	// Some of them can provide additional functionality implemented directly is specific class.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UsePremadeEffectClass = false;

	// Decide whether to overwire the EffectStruct of the chosen clas or to use original values from the class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UsePremadeEffectClass"))
		bool OverwriteEffectClassProperties = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (EditCondition = "UsePremadeEffectClass"))
		TSubclassOf<UEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		EEffectType EffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		FStatsModifierStruct StatsModifierStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		FName EffectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		FString EffectDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		UTexture2D* EffectIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		float Duration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		bool AllowMultiHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!UsePremadeEffectClass || OverwriteEffectClassProperties"))
		int32 HitsNum = 1;

};
