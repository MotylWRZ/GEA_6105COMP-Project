// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackMelee);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackRanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReturnToIdle);

class UAnimMontage;

UENUM(BlueprintType)
enum EAttackMode
{
	Attack_Melee,
	Attack_Ranged,
	Attack_None
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUTHIRDPERSON425_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	///////////////////////////
	// Public Member Functions
	///////////////////////////

	// Custom Component Update
	virtual void CustomTickComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	// Perform Attack from the current attack mode (Melee/Ranged)
	// This should be called in the AnimNotiy class in order to correctly intergrate the attack action with animation
	virtual void PerformAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	// Set a specified Actor as a target
	virtual void SetTarget(AActor* NewTarget);

	//Reset the Attack (it will also clear the current target)
	virtual void ResetAttack();


	//////////////////////
	// Accessors/Mutators
	//////////////////////
	virtual bool CanAttackRanged();
	virtual bool CanAttackMelee();
	virtual bool IsTargetInMeleeRange();
	virtual bool IsTargetInRangedRange();
	FORCEINLINE virtual void SetAttackMode(EAttackMode NewAttackMode) { this->m_CurrentAttackMode = NewAttackMode; }

	// Get the distance to the current target
	virtual float GetDistanceToTarget();

	/////////////
	// Delegates
	/////////////
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttackStart OnAttackStart;
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttack OnAttack;
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttackMelee OnAttackMelee;
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttackRanged OnAttackRanged;
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnReturnToIdle OnReturnToIdle;

protected:
	///////////////////////////
	// Protected Member Functions
	///////////////////////////

	// Start an Attack action
	virtual void AttackStart();
	virtual void PerformMeleeAttack();
	virtual void PerformRangedAttack();

public:
	////////////////////////
	//Public Class Members
	////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		AActor* m_TargetActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		USkeletalMeshComponent* m_AnimatedMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		float m_ComponentUpdateInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
	bool m_IsAttacking;
	//-----------MELEE COMBAT---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat")
		bool m_bIsMeleeActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		UAnimMontage* m_MeleeAnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		int32 m_MeleeAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		float m_MeleeAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		float m_MeleeAttackIntervalDuration;

	// Should apply damage immediately after performing attack action ?
	// OnAttackMelee can be binded into event in order to apply custom or additional effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		bool m_bInstantEffectMelee = true;


	//-----------RANGED COMBAT---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat")
		bool m_bIsRangedActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		UAnimMontage* m_RangedAnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		int32 m_RangedAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		float m_RangedAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		float m_RangedAttackIntervalDuration;

	// Should apply damage immediately after performing attack action ?
	// OnAttackRanged can be binded into event in order to apply custom or additional effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		bool m_bInstantEffectRanged;

private:
	TEnumAsByte<EAttackMode> m_CurrentAttackMode;
	float m_CurrentTime;
	FTimerHandle m_CombatTimerHandle;
};
