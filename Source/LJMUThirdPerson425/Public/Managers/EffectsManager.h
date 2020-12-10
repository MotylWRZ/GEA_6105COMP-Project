// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effects/EffectsStructs.h"
#include "Effects/Effect.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "EffectsManager.generated.h"

// A struct used for storing an TArray of pointers to Effect objects.
// This can allow contaniner nesting in UPROPERTIES variables
USTRUCT()
struct FEffectsArray
{
	GENERATED_BODY()

	UPROPERTY()
		TArray<UEffect*> EffectsArray;
};

UCLASS()
class LJMUTHIRDPERSON425_API UEffectsManager : public UManagerBase
{
	GENERATED_BODY()

public:
	UEffectsManager();
	void Update(float DeltaTime) override;
	void Clear() override;

	UEffect* CreateEffectFromStruct(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);

	UFUNCTION(BlueprintCallable)
	void AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);

	UFUNCTION(BlueprintCallable)
	void AddEffectsToActor(AActor* InstigatorActor, AActor* AffectedActor, const TArray<FEffectStruct>& EffectsStructs);

	UFUNCTION(BlueprintCallable)
	void FindEffectsByActor(AActor* AffectedActor, TArray<UEffect*>& EffectsArray, bool& IsArrayFound);

	// Get EffectsArray by actor's memory address
	// Can return nullptr if there is no value associated with specified actor (i.e there is no key or no valid value)
	const TArray<UEffect*>* GetEffectsByActor(AActor* AffectedActor) const;

	// Add new effect and check if there is already effct with the same type. Then check if the cyrrent one should be replaced.
	// THERE CAN BE NO 2 EFFECTS WITH THE SAME TYPE APPLIED ON THE SAME ACTOR
	// Returns TRUE if current efect has een replaced by new effect.
	// Returns FALSE if CurrentEffect with the same type has not been found or it should remain active
	bool AddAndReplaceEffect(UEffect* EffectToAdd, AActor* AffectedActor);

	UEffect* GetEffectWithHigherStatsScore(UEffect* EffectA, UEffect* EffectB);

	// Get the Effect of the specified type
	// This can return NULL if Effect has not been found
	UEffect* GetEffectAlreadyAppliedByType(EEffectType EffectType, AActor* AffectedActor);

protected:
	bool IsActorAffected(AActor* Actor);

private:
	TMap<AActor*, FEffectsArray> m_EffectsMap;

	int32 UpdateNum;
};
