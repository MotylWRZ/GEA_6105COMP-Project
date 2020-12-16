// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/CanHasEffectsInterface.h"
#include "Interfaces/AttackableInterface.h"

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "AICharacterBase.generated.h"

class USelectableActorComponent;
class UCharacterCombatComponent;

UCLASS()
class LJMUTHIRDPERSON425_API AAICharacterBase : public ACharacterBase, public IAttackableInterface, public ICanHasEffectsInterface
{
	GENERATED_BODY()


public:

	AAICharacterBase();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// IAttackableInterface implementation
	UFUNCTION(BlueprintCallable)
		virtual void ApplyDamage_Implementation(AActor* InstigatorActor, int32 DamageToApply) override;
	UFUNCTION(BlueprintCallable)
		virtual bool IsAlive_Implementation() override;

	// ICanHasEffectsInterface implementation
	UFUNCTION(BlueprintCallable)
		virtual bool CanEffectBeApplied_Implementation(EEffectType EffectType) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterCombatComponent* m_CharacterCombatComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USelectableActorComponent* m_SelectableActorComponent;
};
