// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Utilities/Physics/PhysicsHelpers.h"

#include "Projectiles/ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::SetProjectileTarget(FVector TargetLocation, bool AdjustTransformToHitTarget)
{
	FVector tProjectileLoc = this->GetActorLocation();
	float tProjectileSpeed = this->m_ProjectileMovementComponent->InitialSpeed;

	float tProjectilePitch = UPhysicsHelpers::GetAngleRequiredToHitCoordinate(tProjectileLoc, TargetLocation, tProjectileSpeed);

	FRotator tLookAtRotator = UKismetMathLibrary::FindLookAtRotation(tProjectileLoc, TargetLocation);

	FRotator tNewProjectileRotation = tLookAtRotator;// FRotator(tLookAtRotator.Roll, tProjectilePitch, tLookAtRotator.Yaw);

	this->SetActorRotation(tNewProjectileRotation);

}

void AProjectileBase::SetProjectileTarget(AActor* TargetActor, bool AdjustTransformToHitTarget)
{
	if (!TargetActor)
	{
		return;
	}

	FVector tTargetLocation = TargetActor->GetActorLocation();

	SetProjectileTarget(tTargetLocation, AdjustTransformToHitTarget);
}

void AProjectileBase::SetupProjectileMovement(float InitialSpeed, float MaxSpeed, float GravityScale)
{
	this->m_ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	this->m_ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	this->m_ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
}

