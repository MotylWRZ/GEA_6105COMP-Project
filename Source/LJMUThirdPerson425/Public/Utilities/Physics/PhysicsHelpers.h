// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PhysicsHelpers.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API UPhysicsHelpers : public UObject
{
	GENERATED_BODY()

public:

	// Projectile Motion
	static float GetAngleRequiredToHitCoordinate(FVector SourceLocation, FVector TargetLocation, float Velocity, float GravityScale = 1.0f);
};
