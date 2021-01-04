// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Utilities/General/HelperFunctionsLibrary.h"

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
	virtual void Update(float DeltaTime);

	FORCEINLINE virtual const FAbilityStruct* GetAbilityStruct() const override { return &m_AbilityStructSelf; }
	FORCEINLINE virtual void SetAbilityStruct(FAbilityStruct* AbilityStruct) override { this->m_AbilityStructSelf = *UHelperFunctionsLibrary::CastToDerived<FAbilityStruct_Self>(AbilityStruct); }

	// Class Members
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* m_ParticleSystem;


protected:
	FAbilityStruct_Self m_AbilityStructSelf;
};
