// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effects/EffectsStructs.h"

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "EffectsManager.generated.h"


UCLASS()
class LJMUTHIRDPERSON425_API UEffectsManager : public UManagerBase
{
	GENERATED_BODY()


	virtual void AddEffectToActor(AActor* InstigatorActor, AActor* AffectedActor, FEffectStruct& EffectStruct);

	virtual bool IsActorAffected(AActor* Actor);

private:
	TMap<AActor*, TArray<FEffectStruct>> m_EffectsMap;
};
