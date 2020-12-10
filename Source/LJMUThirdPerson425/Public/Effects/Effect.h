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
	bool InitialiseEffect(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);
	void Update(float DeltaTime);
	void ApplyEffect();

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
	FEffectStruct GetEffectStruct() { return m_EffectStruct; }

	// Get the Effect stats score (all stats summed up)
	UFUNCTION(BlueprintCallable, Category = "Effect")
	float GetEffectStatsScore();

	FORCEINLINE void SetIsActive(bool IsActive) { m_bIsActive = IsActive; if (!IsActive) { OnEffectRemoved.Broadcast(); }; }
	FORCEINLINE void SetHitInterval(float HitInterval) { m_HitInterval = HitInterval; }



	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectAdded OnEffectAdded;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectApplied OnEffectApplied;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectRemoved OnEffectRemoved;
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

	UPROPERTY()
	AActor* m_InstigatorActor;
	UPROPERTY()
	AActor* m_AffectedActor;

	bool m_bCanUseInstigatorStats;
	FActorStatsStruct m_InstigatorActorStats;

	UPROPERTY(EditDefaultsOnly)
	FEffectStruct m_EffectStruct;
};
