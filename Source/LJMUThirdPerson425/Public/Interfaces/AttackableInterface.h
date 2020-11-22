// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Components/ActorStatsComponent.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAttackableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class LJMUTHIRDPERSON425_API IAttackableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage(AActor* InstigatorActor, int32 DamageToApply);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsAlive();
};
