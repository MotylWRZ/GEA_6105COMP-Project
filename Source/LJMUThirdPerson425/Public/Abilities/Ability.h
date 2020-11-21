// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilityStructs.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

DECLARE_DELEGATE_OneParam(FOnAbilityDestroyed, AAbility*);


UCLASS()
class LJMUTHIRDPERSON425_API AAbility : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility();

	// Implement this function in BP in order to extend the UseAbility() function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseAbility();
	// Override this function in child classes
	virtual void UseAbility_Implementation();

	virtual void Initialise(AActor* AbilityUser);

	UFUNCTION(BlueprintCallable)
		virtual void AutoDestroy();

	FOnAbilityDestroyed OnAbilityDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ApplyDamageToActor(AActor* Actor, int32 DamageToApply);
	virtual void AddHealthToActor(AActor* Actor, int32 HealthToAdd);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Class Members
protected:
	AActor* m_AbilityUser;
	USceneComponent* m_RootComponent;
	FTimerHandle m_AbilityTimerHandle;

	bool m_bInitialised;

};
