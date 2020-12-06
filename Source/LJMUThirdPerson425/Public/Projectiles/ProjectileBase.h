// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
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

	virtual void AdjustProjectileVelocityToHitTarget(FVector TargetLocation);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* m_ProjectileMovementComponent;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCollisionSphere* m_CollisionSphereComponent;*/
protected:
private:

};
