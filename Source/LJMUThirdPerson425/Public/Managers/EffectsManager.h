// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effects/EffectsStructs.h"
#include "Effects/Effect.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "EffectsManager.generated.h"

UCLASS()
class LJMUTHIRDPERSON425_API UEffectsManager : public UManagerBase
{
	GENERATED_BODY()

public:
	UEffectsManager();
	virtual void Update(float DeltaTime) override;
	virtual void Clear() override;

	virtual void AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, const FEffectStruct& EffectStruct);
	virtual void AddEffectsToActor(AActor* InstigatorActor, AActor* AffectedActor, const TArray<FEffectStruct>& EffectsStructs);

protected:
	virtual bool IsActorAffected(AActor* Actor);

private:
	TMap<AActor*, TArray<UEffect*>> m_EffectsMap;
};
