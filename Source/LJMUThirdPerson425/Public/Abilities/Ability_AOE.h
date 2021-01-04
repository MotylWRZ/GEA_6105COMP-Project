// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Utilities/General/HelperFunctionsLibrary.h"

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

	FORCEINLINE virtual const FAbilityStruct* GetAbilityStruct() const override { return &m_AOEAbilityStruct; }
	FORCEINLINE virtual void SetAbilityStruct(FAbilityStruct* AbilityStruct) override { this->m_AOEAbilityStruct = *UHelperFunctionsLibrary::CastToDerived<FAbilityStruct_AOE>(AbilityStruct); }

protected:
	virtual void UpdateSphereCollision(float DeltaTime);
	virtual void Update(float DeltaTime) override;

public:
	USceneComponent* m_RootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* m_SphereCollisionComponent;
	TArray<USphereComponent*> m_SphereComponents;
protected:
	FAbilityStruct_AOE m_AOEAbilityStruct;
	// Container of affected actors. It can be used to avoid applying the ability
	// more than once on the actors (damaging more than once per Ability).
	TArray<AActor*>  m_AffectedActors;

};
