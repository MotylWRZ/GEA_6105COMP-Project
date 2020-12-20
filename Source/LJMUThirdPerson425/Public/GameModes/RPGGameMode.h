// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"



/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_SoulsAmountCurrent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	int32 m_SoulsAmountToWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_PortalsCurrentQty;
};
