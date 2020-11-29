// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
		AHeroPlayerController();
		virtual void SetupInputComponent() override;

public:
		virtual void BeginPlay() override;
		virtual void CheckForTarget();
		virtual void SelectHoveredActor();
		virtual void HoverActor(AActor* HoveredActor);
		virtual void MoveCharacter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* m_HoveredActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* m_SelectedActor;
	FTimerHandle m_ControllerTimerHandle;

	FVector m_HitLocation;
};
