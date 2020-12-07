// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Managers/ModifiersManager.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectsStructs.generated.h"

		USTRUCT()
		struct FEffectStruct : public FTableRowBase
	{
		GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FStatsModifierStruct StatsModifierStruct;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float Duration = 1.0f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool AllowIntervals = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			int32 IntervalsNum = 1;


	};