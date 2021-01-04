// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorStatsComponent.h"
#include "CharacterStatsComponent.generated.h"

class UCharacterCombatComponent;
class USpellbook;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnArmorModified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementSpeedModified);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUTHIRDPERSON425_API UCharacterStatsComponent : public UActorStatsComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	////////////////////////////////////////////////////////////////
	/// Stats Modifying functions
	////////////////////////////////////////////////////////////////
	virtual void ModifyArmor(int32 ModifyingValue);
	virtual void ModifySpeed(int32 ModifyingValue);

	// Apply Damage on this Character Stats Component
	virtual void TakeDamage(UPARAM(ref) AActor*& InstigatorActor, int32 DamageToApply) override;

	///////////////////////////////////////////////////////////////////
	/// Getters/Setters
	///////////////////////////////////////////////////////////////////

	//FORCEINLINE const virtual int32& GetMeleeAttack() const { return  m_MeleeAttack; }
	FORCEINLINE const virtual int32& GetSpeed() const { return m_MovementSpeed; }


	//FORCEINLINE virtual void SetMeleeAttack(int32 NewAttack) { m_MeleeAttack = NewAttack; }
	FORCEINLINE virtual void SetSpeed(int32 NewSpeed)   { m_MovementSpeed = NewSpeed; }

	///////////////////////////////////////////////////////
	//Delegates
	///////////////////////////////////////////////////////
	UPROPERTY(BlueprintAssignable, Category = "CharacterStatsComponent")
	FOnArmorModified OnArmorModified;

	UPROPERTY(BlueprintAssignable, Category = "CharacterStatsComponent")
	FOnMovementSpeedModified OnMovementSpeedModified;

protected:

	virtual void UpdateCharacterSpeed();

	////////////////
	// Class Members
	////////////////
	// Stats
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_Armor = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_ArmorMax = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_MovementSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_MovementSpeedMax = 300;
};
