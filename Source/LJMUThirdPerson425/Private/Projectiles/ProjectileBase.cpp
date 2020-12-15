// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/General/HelperFunctionsLibrary.h"

#include "Components/ActorStatsComponent.h"

#include "Projectiles/ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
	: m_ProjectileOwner(nullptr)
	, m_HitActorsCurrent(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	this->m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	this->m_CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));

	this->RootComponent = this->m_CollisionSphereComponent;

	this->m_ProjectileHitParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileHitParticleSystemComponent"));

	this->m_ProjectileHitParticleSystem->bAutoActivate = false;
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

void AProjectileBase::Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct, FProjectileStruct* ProjectileStruct)
{
	if (!ProjectileOwner)
	{
		return;
	}

	this->m_ProjectileOwner = ProjectileOwner;

	if (ProjectileStruct)
	{
		this->m_ProjectileStruct = *ProjectileStruct;
	}

	if (StatsModifierStruct)
	{
		this->m_StatsModifierStruct = *StatsModifierStruct;
	}

	m_CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(this->m_ProjectileTimerHandle, this, &AProjectileBase::DestroyProjectile, this->m_ProjectileStruct.DurationMax, false);
}

void AProjectileBase::Initialise(AActor* ProjectileOwner, FStatsModifierStruct* StatsModifierStruct, int32 HitActorsMax, bool IgnoreAlliesHit, float DurationMax)
{
	FProjectileStruct tProjectileStruct;

	tProjectileStruct.HitActorsMax = HitActorsMax;
	tProjectileStruct.DurationMax = DurationMax;
	tProjectileStruct.bIgnoreAlliesHit = IgnoreAlliesHit;

	this->Initialise(ProjectileOwner, StatsModifierStruct, &tProjectileStruct);
}

void AProjectileBase::AdjustProjectileVelocityToHitTarget(FVector TargetLocation)
{
	FVector tTossVelocity;

	// Save the syggesetd projectile velocity into tTossVelocity vector
	UGameplayStatics::SuggestProjectileVelocity(GetWorld(), tTossVelocity, this->GetActorLocation(), TargetLocation, this->m_ProjectileMovementComponent->InitialSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	// Set current projectile velocity
	this->m_ProjectileMovementComponent->Velocity = tTossVelocity;
}

void AProjectileBase::DestroyProjectile()
{

	OnProjectileDestroyed.Broadcast();
	this->Destroy();
}

void AProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this->m_ProjectileStruct.bIgnoreAlliesHit)
	{
		if (!UActorStatsComponent::IsEnemyByActor(this->m_ProjectileOwner, OtherActor))
		{
			// Return if overlapped actor is an ally for the projectile owner
			return;
		}
	}

	if (UModifiersManager::ModifyActorStats(this->m_ProjectileOwner, OtherActor, this->m_StatsModifierStruct))
	{
		this->UpdateHitActors();

		this->m_ProjectileHitParticleSystem->SetWorldLocation(this->GetActorLocation());
		this->m_ProjectileHitParticleSystem->SetActive(true);

		this->OnProjectileHit.Broadcast();
	}
	else
	{
		this->OnProjectileMiss.Broadcast();
	}


}

void AProjectileBase::SetIsProjectileActive(bool IsActive)
{
	if (!IsActive)
	{
		// Disable Overlap Events generation
		this->m_CollisionSphereComponent->SetGenerateOverlapEvents(false);
	}

	this->m_bIsProjectileActive = IsActive;

}

void AProjectileBase::UpdateHitActors()
{
	this->m_HitActorsCurrent++;

	if (this->m_HitActorsCurrent >= this->m_ProjectileStruct.HitActorsMax)
	{
		this->SetIsProjectileActive(false);
	}
}
