// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

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

	virtual void SetProjectileTarget(FVector TargetLocation, bool AdjustTransformToHitTarget);
	virtual void SetProjectileTarget(AActor* TargetActor, bool AdjustTransformToHitTarget);

	// Setup Projectile base  movement properties
	// Can be called after spawning
	virtual void SetupProjectileMovement(float InitialSpeed = 2000.0f, float MaxSpeed = 2000.0f, float GravityScale = 1.0f);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* m_ProjectileMovementComponent;
protected:
private:

};
