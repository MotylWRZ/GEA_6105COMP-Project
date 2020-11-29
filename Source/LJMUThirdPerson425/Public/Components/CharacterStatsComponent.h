// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorStatsComponent.h"
#include "CharacterStatsComponent.generated.h"

class UCharacterCombatComponent;
class USpellbook;

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

	/////////////////////////////
	/// Stats Modifying functions
	/////////////////////////////
	//virtual void ModifyMeleeAttack(int32 ModifyingValue);
	virtual void ModifySpeed(int32 ModifyingValue);
	virtual void ModifyMana(int32 ModifyingValue);


	//////////////////
	/// Getters/Setters
	//////////////////

	//FORCEINLINE const virtual int32& GetMeleeAttack() const { return  m_MeleeAttack; }
	FORCEINLINE const virtual int32& GetSpeed() const { return m_Speed; }
	FORCEINLINE const virtual int32& GetMana() const { return m_Mana; }

	//FORCEINLINE virtual void SetMeleeAttack(int32 NewAttack) { m_MeleeAttack = NewAttack; }
	FORCEINLINE virtual void SetSpeed(int32 NewSpeed)   { m_Speed = NewSpeed; }
	FORCEINLINE virtual void SetMana(int32 NewMana)		{ m_Mana = NewMana; }

	////////////////
	// Class Members
	////////////////
	// Stats
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_Mana;

};
