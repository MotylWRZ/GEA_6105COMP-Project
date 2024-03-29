// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"Projectiles/ProjectileBase.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackMelee);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackRanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReturnToIdle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewTargetSet, AActor*, NewTargetRef);

class UAnimMontage;
class AProjectileBase;
class USoundCue;

UENUM(BlueprintType)
enum EAttackMode
{
	Attack_Melee,
	Attack_Ranged,
	Attack_None
};

USTRUCT(Blueprintable)
struct FCombatStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackIntervalDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* AttackSound;

	// Should apply damage immediately after performing attack action ?
	// On Attack can be binded into event in order to apply custom or additional effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInstantEffect = true;
};

USTRUCT(Blueprintable)
struct FRangedCombatStruct : public FCombatStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseProjectiles = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UseProjectiles"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	// Customise projectile using ProjectileStruct
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UseProjectiles"))
	FProjectileStruct ProjectileStruct;

	// Projectile Launch location relative to the component owner actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "UseProjectiles"))
	FVector ProjectileLaunchRelativeLocation;
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

	virtual void ShootProjectile();
	void PlayAttackSound();


	//////////////////////
	// Accessors/Mutators
	//////////////////////
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttackRanged();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttackMelee();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsTargetInMeleeRange();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsTargetInRangedRange();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackMode(EAttackMode NewAttackMode) { this->m_CurrentAttackMode = NewAttackMode; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	// Get the distance to the current target
	float GetDistanceToTarget();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AActor* const GetCurrentTarget() const { return m_TargetActor; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool const IsAttacking() const { return m_bIsAttacking; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		static UCombatComponent* GetCombatComponent(AActor* FromActor);

	/////////////
	// Delegates
	/////////////
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnAttackStart OnAttackStart;
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnAttack OnAttack;
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnAttackMelee OnAttackMelee;
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnAttackRanged OnAttackRanged;
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnReturnToIdle OnReturnToIdle;
	UPROPERTY(BlueprintAssignable, Category = "CombatDelegates")
		FOnNewTargetSet OnNewTargetSet;

protected:
	///////////////////////////
	// Protected Member Functions
	///////////////////////////

	// Start an Attack action
	virtual void AttackStart();
	virtual void PerformMeleeAttack();
	virtual void PerformRangedAttack();

	// returns distance to target using line trace
	virtual float GetTargetDistanceWithLineTrace();

public:
	////////////////////////
	//Public Class Members
	////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		USkeletalMeshComponent* m_AnimatedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		// If Enabled, the attack will start automatically once the target is within attack range
		// Additionally the Attack Mode will be automatically picked, based on the current target distance (target is far - RangedMode/ target is close - MeleeMode)
		// If Disabled, the attack must be called explicitly (call Attack Start )
		bool m_bAutoAttackModeEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Component")
		// Combat component update frequency.
		// AutoAttackModeEnabled must be set to TRUE in order to enable Component updating
		float m_ComponentUpdateInterval;

	//-----------MELEE COMBAT---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat")
		bool m_bIsMeleeActive = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Combat", meta = (EditCondition = "m_bIsMeleeActive"))
		FCombatStruct m_MeleeCombatStruct;

	//-----------RANGED COMBAT---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat")
		bool m_bIsRangedActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Combat", meta = (EditCondition = "m_bIsRangedActive"))
		FRangedCombatStruct m_RangedCombatStruct;

protected:
	AActor* m_TargetActor;
	TEnumAsByte<EAttackMode> m_CurrentAttackMode;
	FTimerHandle m_CombatTimerHandle;
	float m_CurrentTime;
	bool m_bIsAttacking;
};
