// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effects/EffectsStructs.h"
#include "Effects/Effect.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "EffectsManager.generated.h"

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

	UFUNCTION(BlueprintCallable)
	void AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);

	UFUNCTION(BlueprintCallable)
	void AddEffectsToActor(AActor* InstigatorActor, AActor* AffectedActor, const TArray<FEffectStruct>& EffectsStructs);

	UFUNCTION(BlueprintCallable)
	void FindEffectsByActor(AActor* AffectedActor, TArray<UEffect*>& EffectsArray, bool& IsArrayFound);

	// Get EffectsArray by actor's memory address
	// Can return nullptr if there is no value associated with specified actor (i.e there is no key or no valid value)
	const TArray<UEffect*>* GetEffectsByActor(AActor* AffectedActor) const;

protected:
	bool IsActorAffected(AActor* Actor);

private:
	TMap<AActor*, FEffectsArray> m_EffectsMap;

	int32 UpdateNum;
};
