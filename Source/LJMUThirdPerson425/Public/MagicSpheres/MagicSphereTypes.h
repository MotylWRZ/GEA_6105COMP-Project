//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicSphereTypes.generated.h"


/**
 *
 */
UENUM(BlueprintType)
enum EMagicSphereTypes
{
	Sphere_Ice			UMETA(Displayname = "Ice"),
	Sphere_Pyromancy   UMETA(Displayname = "Pyromancy"),
	Sphere_Healing      UMETA(Displayname = "Healing")
};
