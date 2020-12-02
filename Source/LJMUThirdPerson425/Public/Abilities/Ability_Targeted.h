// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Utilities/General/HelperFunctionsLibrary.h"

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "Ability_Targeted.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API AAbility_Targeted : public AAbility
{
	GENERATED_BODY()
public:
	AAbility_Targeted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Initialise(AActor* AbilityUser) override;

	void UseAbility();
	virtual void UseAbility_Implementation() override;


	FORCEINLINE virtual const FAbilityStruct* GetAbilityStruct() const override { return &m_AbilityTargetedStruct; }
	FORCEINLINE virtual void SetAbilityStruct(FAbilityStruct* AbilityStruct) override { this->m_AbilityTargetedStruct = *UHelperFunctionsLibrary::CastToDerived<FAbilityStruct_Targeted>(AbilityStruct); }

	// Class Members
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* m_ParticleSystem;

	int32 m_CurrentInterval;

protected:
	FAbilityStruct_Targeted m_AbilityTargetedStruct;
	AActor* m_TargetActor;
};
