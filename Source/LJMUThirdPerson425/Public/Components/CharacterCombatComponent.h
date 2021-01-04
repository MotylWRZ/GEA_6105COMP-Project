// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CombatComponent.h"
#include "CharacterCombatComponent.generated.h"

class ACharacter;


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LJMUTHIRDPERSON425_API UCharacterCombatComponent : public UCombatComponent
{
public:
	UCharacterCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void AttackStart() override;

	// Custom Component Update override
	virtual void CustomTickComponent() override;

	virtual void PerformMeleeAttack() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void ResetAttack() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charater Combat")
	// If the character is fighting (target is within range), disable movement
	// Movement will be automatically enabled, once the character stops fighting
	bool m_bDisableMovementDuringAttack;
private:
	ACharacter* m_Owner;

};
