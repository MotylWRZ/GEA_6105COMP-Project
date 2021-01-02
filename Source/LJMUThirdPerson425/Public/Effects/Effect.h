// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EffectsStructs.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectAdded, UEffect*, EffectPtr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectApplied, UEffect*, EffectPtr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectRemoved);

UCLASS(Blueprintable)
class LJMUTHIRDPERSON425_API UEffect : public UObject
{
	GENERATED_BODY()

public:
	UEffect();
	virtual bool InitialiseEffect(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);
	virtual void Update(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyEffect();
	void ApplyEffect_Implementation();

	///////////////////////
	// Accessors/Mutators
	///////////////////////
	UFUNCTION(BlueprintCallable, Category = "Effect")
	bool const IsActive() const { return m_bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetHitInterval() const { return m_HitInterval; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetCurrentDuration() const { return m_CurrentDuration; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetDurationLeft() const { return m_EffectStruct.Duration - m_CurrentDuration; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	FEffectStruct const GetEffectStruct() const { return m_EffectStruct; }

	// Get the Effect stats score (all stats summed up)
	UFUNCTION(BlueprintCallable, Category = "Effect")
	float GetEffectStatsScore();

	void SetIsActive(bool IsActive);
	FORCEINLINE void SetHitInterval(float HitInterval) { m_HitInterval = HitInterval; }
	// Add the stats changes into AccumulatedStatsChanges struct and store them there
	FORCEINLINE void AccumulateStatsChanges(const FStatsModifierStruct& StatsModifierStruct) { m_AccumulatedStatsChanges = m_AccumulatedStatsChanges + StatsModifierStruct; }
	FORCEINLINE bool IsSuccess() { return FMath::RandRange(1, 100) <= m_EffectStruct.SuccessChance ? true : false; }
	// Undo any stats changes that have been made by this effect
	void UndoStatsChangesOnTarget();

	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectAdded OnEffectAdded;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectApplied OnEffectApplied;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectRemoved OnEffectRemoved;

protected:
	UPROPERTY()
		AActor* m_InstigatorActor;
	UPROPERTY(BlueprintReadWrite)
		AActor* m_AffectedActor;

	bool m_bCanUseInstigatorStats;
	FActorStatsStruct m_InstigatorActorStats;
	FStatsModifierStruct m_AccumulatedStatsChanges;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FEffectStruct m_EffectStruct;

private:
	// This should be changed to false if the effect Duration <= 0.0f
	bool m_bIsActive = true;
	bool m_bFirstEffectApplied;

	// HitInterval should be based on the number of hits (HitsNum) and Duration of effect
	// Example equation can be: Duration/HitsNum = HitInterval
	// Examle: 1.0f/3 = 0.333f
	float m_HitInterval = 0.0f;
	float m_CurrentHitInterval;

	float m_CurrentDuration;
	int32 m_CurrentHitNum;
};
