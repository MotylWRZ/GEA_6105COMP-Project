// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilityStructs.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

DECLARE_DELEGATE_OneParam(FOnAbilityDestroyed, AAbility*);


UCLASS(Abstract)
class LJMUTHIRDPERSON425_API AAbility : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	///////////////////////////
	// Public Member Functions
	///////////////////////////
public:
	// Implement this function in BP in order to extend the UseAbility() function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseAbility();
	// Override this function in child classes
	virtual void UseAbility_Implementation();

	virtual void Initialise(AActor* AbilityUser);
	virtual void Update(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void AutoDestroy();

	FOnAbilityDestroyed OnAbilityDestroyed;
	///////////////////////////
	// Accesors/Mutators
	///////////////////////////
	UFUNCTION(BlueprintCallable)
	AActor* const GetAbilityUser() const { return m_AbilityUser; }
	UFUNCTION(BlueprintCallable)
	float GetDesiredUpdateInterval() { return m_DesiredUpdateInterval; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAbilityActive() { return m_bIsAbilityActive; }
	UFUNCTION(BlueprintCallable)
	void SetDesiredUpdateInterval(float NewDesiredUpdateFrequency);

	UFUNCTION(BlueprintCallable)
	void SetIsAbilityActive(bool IsActive) { m_bIsAbilityActive = IsActive; }

	///////////////////////////
	// Protected Member Functions
	///////////////////////////
protected:
	virtual void ApplyDamageToActor(AActor* Actor, int32 DamageToApply);
	virtual void AddHealthToActor(AActor* Actor, int32 HealthToAdd);



	// Class Members
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float m_DesiredUpdateInterval;
protected:
	AActor* m_AbilityUser;
	USceneComponent* m_RootComponent;

	bool m_bInitialised;
	bool m_bShouldUpdate;
	bool m_bIsAbilityActive;
	float m_CurrentUpdateInterval;

};
