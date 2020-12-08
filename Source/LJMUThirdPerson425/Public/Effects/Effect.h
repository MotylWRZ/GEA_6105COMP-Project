// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EffectsStructs.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

/**
 *
 */
UCLASS()
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
	FORCEINLINE bool const IsActive() const { return m_IsActive; }
	FORCEINLINE float const GetHitInterval() const { return m_HitInterval; }
	FORCEINLINE float const GetCurrentDuration() const { return m_CurrentDuration; }
	FORCEINLINE float const GetDurationLeft() const { return m_EffectStruct.Duration - m_CurrentDuration; }

	FORCEINLINE void SetIsActive(bool IsActive) { m_IsActive = IsActive; }
	FORCEINLINE void SetHitInterval(float HitInterval) { m_HitInterval = HitInterval; }

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
