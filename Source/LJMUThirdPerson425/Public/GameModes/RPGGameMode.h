// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerWon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLost);

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

		UFUNCTION(BlueprintCallable)
		void AddSouls(int32 SoulsAmountToAdd);
		UFUNCTION(BlueprintCallable)
		void RemoveSouls(int32 SoulsAmountToRemove);
		UFUNCTION(BlueprintCallable)
		void DecrementSoulsQty();

		UFUNCTION(BlueprintCallable)
		void IncrementPortalsQty();
		UFUNCTION(BlueprintCallable)
		void DecrementPortalsQty();

		UFUNCTION()
		void PlayerWon();
		UFUNCTION()
		void PlayerLost();
		void CheckWinningCondition();

		///////////////////////////////////////////////
		//Delegates
		///////////////////////////////////////////////
		UPROPERTY(BlueprintAssignable, Category = "RPGGameMode")
		FOnPlayerWon OnPlayerWon;
		UPROPERTY(BlueprintAssignable, Category = "RPGGameMode")
		FOnPlayerLost OnPlayerLost;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_SoulsAmountCurrent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	int32 m_SoulsAmountToWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_PortalsCurrentQty;
};
