// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorDamaged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorHealed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorDestroyed);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUTHIRDPERSON425_API UActorStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/////////////////////////////
	/// Stats Modifying functions
	/////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyHealth(int32 ModifyingValue);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyMaxHealth(int32 ModifyingValue);

	// Apply Damage on this Stats Component
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void TakeDamage(UPARAM(ref) AActor*& InstigatorActor, int32 DamageToApply); //{ ModifyHealth(-DamageToApply); }
	// Add Health for this Stats Component. The final value will be clamped by the MaxHealth value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void AddHealth(UPARAM(ref) AActor*& InstigatorActor, int32 HealthToAdd); //{ ModifyHealth(HealthToAdd); }




	//////////////////
	/// Getters/Setters
	//////////////////

	UFUNCTION(BlueprintCallable, Category = "Stats")
	static UActorStatsComponent* GetStatsComponent(AActor* FromActor);

	FORCEINLINE const virtual FName& GetName() const		{ return m_Name; }
	FORCEINLINE const virtual FText& GetDescription() const { return m_Description; }
	FORCEINLINE const virtual int32& GetHealth() const		{ return m_Health; }
	FORCEINLINE const virtual int32& GetHealthMax() const	{ return m_HealthMax; }
	FORCEINLINE const virtual int32& GetTeamID() const		{ return m_TeamID; }

	UFUNCTION(BlueprintPure, Category = "Stats")
	FORCEINLINE bool IsAlive()   { return m_Health > 0; }

	// Check if Actor1 is an enemy for the Actor2
		UFUNCTION(BlueprintPure, Category = "Stats")
	static bool IsEnemyByActor(AActor* Actor1, AActor* Actor2);
	// Check if two stats component should refers to each other as enemies or allies
		UFUNCTION(BlueprintPure, Category = "Stats")
	static bool IsEnemyByComponent(UActorStatsComponent* StatsComponent1, UActorStatsComponent* StatsComponent2);

	FORCEINLINE virtual void SetName		(FName NewName)		   { m_Name = NewName; }
	FORCEINLINE virtual void SetDescription (FText NewDescription) { m_Description = NewDescription; }
	FORCEINLINE virtual void SetHealth		(int32 NewHealth)	   { m_Health = NewHealth; }
	FORCEINLINE virtual void SetHealthMax	(int32 NewHealthMax)   {m_HealthMax = NewHealthMax; }
	FORCEINLINE virtual void SetTeamID		(int32 NewTeamID)	   { m_TeamID = NewTeamID; }

	/////////////
	// Delegates
	/////////////
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnActorDamaged OnActorDamaged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnActorHealed OnActorHealed;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnActorDestroyed OnActorDestroyed;


	// Class Members

	// Stats
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FName m_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FText m_Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
	int32 m_HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 m_TeamID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool m_CanBeDamaged = true;

};
