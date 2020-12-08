// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EffectsStructs.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectAdded, UEffect*, EffectPtr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectApplied, UEffect*, EffectPtr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectRemoved, UEffect*, EffectPtr);

/**
 *
 */
UCLASS(Blueprintable)
class LJMUTHIRDPERSON425_API UEffect : public UObject
{
	GENERATED_BODY()

public:
	UEffect(const FObjectInitializer& ObjectInitializer);
	void InitialiseEffect(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);
	void Update(float DeltaTime);
	void ApplyEffect();

	///////////////////////
	// Accessors/Mutators
	///////////////////////
	UFUNCTION(BlueprintCallable, Category = "Effect")
	bool const IsActive() const { return m_IsActive; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetHitInterval() const { return m_HitInterval; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetCurrentDuration() const { return m_CurrentDuration; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	float const GetDurationLeft() const { return m_EffectStruct.Duration - m_CurrentDuration; }

	UFUNCTION(BlueprintCallable, Category = "Effect")
	FEffectStruct GetEffectStruct() { return m_EffectStruct; }

	FORCEINLINE void SetIsActive(bool IsActive) { m_IsActive = IsActive; }
	FORCEINLINE void SetHitInterval(float HitInterval) { m_HitInterval = HitInterval; }

	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectAdded OnEffectAdded;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectApplied OnEffectApplied;
	UPROPERTY(BlueprintAssignable, Category = "Effect Delegates")
	FOnEffectRemoved OnEffectRemoved;
private:
	// This should be changed to false if the effect Duration <= 0.0f
	bool m_IsActive = true;

	// HitInterval should be based on the number of hits (HitsNum) and Duration of effect
	// Example equation can be: Duration/HitsNum = HitInterval
	// Examle: 1.0f/3 = 0.333f
	float m_HitInterval = 0.0f;

	float m_CurrentDuration;
	int32 m_CurrentHitNum;

	AActor* m_InstigatorActor;
	AActor* m_AffectedActor;

	FEffectStruct m_EffectStruct;
};
