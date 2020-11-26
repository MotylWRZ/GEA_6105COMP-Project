// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Ability_AOE.generated.h"

class USphereComponent;

UCLASS()
class LJMUTHIRDPERSON425_API AAbility_AOE : public AAbility
{
	GENERATED_BODY()

public:
	AAbility_AOE();
	virtual void BeginPlay() override;

	virtual void Initialise(AActor* AbilityUser) override;

		virtual void UseAbility_Implementation() override;



protected:
	virtual void UpdateSphereCollision();
	virtual void ApplyDamageToActor(AActor* Actor, int32 DamageToApply) override;
	virtual void AddHealthToActor(AActor* Actor, int32 HealthToAdd) override;


public:
	USceneComponent* m_RootComponent;
	FAbilityStruct_AOE m_AOEAbilityStruct;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* m_SphereCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float m_ChangeFrequency;

	// Container of affected actors. It can be used to avoid applying the ability
	// more than once on the actors (damaging more than once per Ability).
	TArray<AActor*>  m_AffectedActors;

};
