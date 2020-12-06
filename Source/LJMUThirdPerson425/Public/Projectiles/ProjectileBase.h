// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Managers/ModifiersManager.h"

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

//class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class LJMUTHIRDPERSON425_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct, int32 HitActorsMax = 1);


	virtual void AdjustProjectileVelocityToHitTarget(FVector TargetLocation);

	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetIsProjectileActive(bool IsActive);
protected:
	virtual void UpdateHitActors();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* m_ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* m_CollisionSphereComponent;
protected:
	UPROPERTY()
	AActor* m_ProjectileOwner;

	UPROPERTY()
	FStatsModifierStruct m_StatsModifierStruct;

	UPROPERTY()
	int32 m_HitActorsMax;

	bool m_bIsProjectileActive;
private:
	int32 m_HitActorsCurrent;
};
