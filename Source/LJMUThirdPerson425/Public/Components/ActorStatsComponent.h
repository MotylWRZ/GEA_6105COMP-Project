// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorDamaged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorHealed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsModified);


USTRUCT(Blueprintable)
struct FActorStatsStruct
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0"))
		int32 HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 TeamID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool CanBeDamaged = true;

};



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
	virtual void ModifyHealth(int32 ModifyingValue);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual void ModifyMaxHealth(int32 ModifyingValue);

	// Apply Damage on this Stats Component
	UFUNCTION(BlueprintCallable, Category = "Stats")
		virtual void TakeDamage(UPARAM(ref) AActor*& InstigatorActor, int32 DamageToApply);
	// Add Health for this Stats Component. The final value will be clamped by the MaxHealth value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		virtual void AddHealth(UPARAM(ref) AActor*& InstigatorActor, int32 HealthToAdd);

	//////////////////
	/// Getters/Setters
	//////////////////

	UFUNCTION(BlueprintCallable, Category = "Stats")
	static UActorStatsComponent* GetStatsComponent(AActor* FromActor);

	FORCEINLINE const virtual FName& GetName() const		{ return m_ActorStats.Name; }
	FORCEINLINE const virtual FText& GetDescription() const { return m_ActorStats.Description; }
	FORCEINLINE const virtual int32& GetHealth() const		{ return m_ActorStats.Health; }
	FORCEINLINE const virtual int32& GetHealthMax() const	{ return m_ActorStats.HealthMax; }
	FORCEINLINE const virtual int32& GetTeamID() const		{ return m_ActorStats.TeamID; }
	FORCEINLINE const virtual FActorStatsStruct& GetActorStatsStruct() { return m_ActorStats; }

	UFUNCTION(BlueprintPure, Category = "Stats")
	FORCEINLINE bool IsAlive()   { return m_ActorStats.Health > 0; }

	// Check if Actor1 is an enemy for the Actor2
		UFUNCTION(BlueprintPure, Category = "Stats")
	static bool IsEnemyByActor(AActor* Actor1, AActor* Actor2);
	// Check if two stats component should refers to each other as enemies or allies
		UFUNCTION(BlueprintPure, Category = "Stats")
	static bool IsEnemyByComponent(UActorStatsComponent* StatsComponentA, UActorStatsComponent* StatsComponentB);
	// Compare two StatsStruct in order to determine if their owners should refer to each other as enemies
		UFUNCTION(BlueprintPure, Category = "Stats")
	static bool IsEnemyByStatsStruct(const FActorStatsStruct& StatsStructA, const FActorStatsStruct& StatsStructB);

	FORCEINLINE virtual void SetName		(FName NewName)		   { m_ActorStats.Name = NewName; }
	FORCEINLINE virtual void SetDescription (FText NewDescription) { m_ActorStats.Description = NewDescription; }
	FORCEINLINE virtual void SetHealth		(int32 NewHealth)	   { m_ActorStats.Health = NewHealth; }
	FORCEINLINE virtual void SetHealthMax	(int32 NewHealthMax)   { m_ActorStats.HealthMax = NewHealthMax; }
	FORCEINLINE virtual void SetTeamID		(int32 NewTeamID)	   { m_ActorStats.TeamID = NewTeamID; }

	/////////////
	// Delegates
	/////////////
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FOnActorDamaged OnActorDamaged;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FOnActorHealed OnActorHealed;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FOnActorKilled OnActorKilled;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FOnStatsModified OnActorHealthModified;


	// Class Members

	// Stats
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FActorStatsStruct m_ActorStats;
};
