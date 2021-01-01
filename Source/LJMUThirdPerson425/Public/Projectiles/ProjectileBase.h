// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Managers/ModifiersManager.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileMiss);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileDestroyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileDeactivated);

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USoundCue;

USTRUCT(Blueprintable)
struct FProjectileStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		// Specify Maximum Actors that this projectile can hit. If it is > 1, projectile will continue
		// movement and will hit any other actor until number of hit Actos will be equal to the MaximumHitActors
		int32 HitActorsMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		// Specify the MAX duration of the projectile. it will be destroyed immediately after exceeding this duration
		float DurationMax = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		// If TRUE, continue projectile movement and overlap any encountered allies
		bool bIgnoreAlliesHit = true;
};


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
	virtual void Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct, FProjectileStruct* ProjectileStruct);
	virtual void Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct, int32 HitActorsMax = 1, bool IgnoreAlliesHit = true, float DurationMax = 1.0f);
	virtual void AdjustProjectileVelocityToHitTarget(FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyProjectile();

	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetIsProjectileActive(bool IsActive);


//////////////
// DELEGATES
//////////////
	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FOnProjectileHit OnProjectileHit;
	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FOnProjectileHit OnProjectileMiss;
	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FOnProjectileDestroyed OnProjectileDestroyed;
	UPROPERTY(BlueprintAssignable, Category = "Projectile")
		FOnProjectileDestroyed OnProjectileDeactivated;


protected:
	virtual void UpdateHitActors();
	//virtual void OnProjectileHit();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* m_ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* m_CollisionSphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* m_ProjectileHitParticleSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* m_RootComponent;
protected:
	UPROPERTY()
	AActor* m_ProjectileOwner;

	UPROPERTY(EditDefaultsOnly)
	FProjectileStruct m_ProjectileStruct;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// Specify what changes will be made in the projectile target stats
	FStatsModifierStruct m_StatsModifierStruct;
	FTimerHandle m_ProjectileTimerHandle;

	bool m_bIsProjectileActive;
private:
	int32 m_HitActorsCurrent;
};
