// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

#include "Components/CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try to update the character initial speed.
	this->UpdateCharacterSpeed();
}


// Called every frame
void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStatsComponent::ModifyArmor(int32 ModifyingValue)
{
	this->m_Armor += ModifyingValue;

	if (this->m_Armor < 0)
	{
		this->m_Armor = 0;
	}

	this->OnArmorModified.Broadcast();
}

void UCharacterStatsComponent::ModifySpeed(int32 ModifyingValue)
{
	this->m_MovementSpeed += ModifyingValue;

	if (this->m_MovementSpeed < 0)
	{
		this->m_MovementSpeed = 0;
	}

	this->OnMovementSpeedModified.Broadcast();
	this->UpdateCharacterSpeed();
}

void UCharacterStatsComponent::TakeDamage(UPARAM(ref)AActor*& InstigatorActor, int32 DamageToApply)
{
	float tArmor = static_cast<float>(this->m_Armor);
	float tDamage = static_cast<float>(DamageToApply);

	// Calculate the damage multiplier using simple formula : damage/(damage + armor)
	float tDamageMultiplier = tDamage / (tDamage + tArmor);

	// Calculate the final damage to be applied
	float tFinalDamage = tDamage * tDamageMultiplier;

	int32 tFinalDamageInt = FMath::RoundToInt(tFinalDamage);

	if (tFinalDamage < 0)
	{
		tFinalDamage = 0;
	}

	Super::TakeDamage(InstigatorActor, tFinalDamage);
}

void UCharacterStatsComponent::UpdateCharacterSpeed()
{
	AActor* tOwner = this->GetOwner();

	// Try to retrieve a CharacterMovementComponent in order to change the speed
	UCharacterMovementComponent* tCharactermovementComponent = Cast<UCharacterMovementComponent>(tOwner->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

	if (!tCharactermovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot update the speed of %s. CharacterMovementComponent cannot be found on this actor. !"), *tOwner->GetName());
		return;
	}

	tCharactermovementComponent->MaxWalkSpeed = this->m_MovementSpeed;
}
