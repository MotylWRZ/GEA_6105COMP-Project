// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/General/HelperFunctionsLibrary.h"

#include "Components/ActorStatsComponent.h"

#include "Projectiles/ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	this->m_CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
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

void AProjectileBase::Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct)
{
	this->m_ProjectileOwner = ProjectileOwner;
	this->m_StatsModifierStruct = *StatsModifierStruct;

	m_CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);
}

void AProjectileBase::AdjustProjectileVelocityToHitTarget(FVector TargetLocation)
{
	FVector tTossVelocity;

	UGameplayStatics::SuggestProjectileVelocity(GetWorld(), tTossVelocity, this->GetActorLocation(), TargetLocation, this->m_ProjectileMovementComponent->InitialSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	this->m_ProjectileMovementComponent->Velocity = tTossVelocity;
}

void AProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		UModifiersManager::ModifyActorStats(this->m_ProjectileOwner, OtherActor,  this->m_StatsModifierStruct);
}
