// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/Ability.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "AbilitiesManager.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API AAbilitiesManager : public AManagerBase
{
	GENERATED_BODY()
public:
	AAbilitiesManager();
	virtual void Update() override;

	UFUNCTION(BlueprintCallable)
	AAbility* CreateAbility(TSubclassOf<AAbility> AbilityClass, AActor* AbilityUser);
};
