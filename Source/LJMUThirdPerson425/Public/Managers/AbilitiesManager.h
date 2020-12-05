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
class LJMUTHIRDPERSON425_API UAbilitiesManager : public UManagerBase
{
	GENERATED_BODY()
public:
	UAbilitiesManager();
	//virtual void Tick(float DeltaTime) override;
	virtual void Update(float DeltaTime) override;
	virtual void Clear() override;

	UFUNCTION(BlueprintCallable)
	// Create an new instance of Ability from the specific class.
	// Returns UNINITIALISED ability
	AAbility* CreateAbility(TSubclassOf<AAbility> AbilityClass);

	// Spawn and initialise ability instance of a given class
	AAbility* SpawnAbility(TSubclassOf<AAbility> AbilityClass, AActor* AbilityUser);
	// Spawn and initialise ability instance from  AbilityCustomisedStruct
	AAbility* SpawnCustomisedAbilityFromStruct(FAbilityStructCustomised* AbilityCustomisedStruct, AActor* AbilityUser);

private:
	TArray<AAbility*> m_ActiveAbilities;
	TArray<AAbility*> m_InactiveAbilities;
};
