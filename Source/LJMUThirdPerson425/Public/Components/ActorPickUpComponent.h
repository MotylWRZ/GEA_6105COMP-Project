// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ActorPickUpComponent.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API UActorPickUpComponent : public USphereComponent
{
	GENERATED_BODY()
public:
	UActorPickUpComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPickupSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	float m_PickupRadious;
};
