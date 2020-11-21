// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Ability_Self.generated.h"

class UParticleSystemComponent;

UCLASS()
class LJMUTHIRDPERSON425_API AAbility_Self : public AAbility
{
	GENERATED_BODY()

public:
	AAbility_Self();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Initialise(AActor* AbilityUser) override;

	void UseAbility();
	virtual void UseAbility_Implementation() override;

	// Class Members
public:
	FAbilityStruct_Self m_AbilityStructSelf;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* m_ParticleSystem;

	int32 m_CurrentInterval;
};
