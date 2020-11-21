// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Spells/Spell.h"
#include "MagicSphereTypes.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "MagicSphere.generated.h"





USTRUCT(Blueprintable)
struct FMagicSphere : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EMagicSphereTypes> MagicSphereType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SphereName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SphereDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* SphereIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSpellStruct> Spells;
};