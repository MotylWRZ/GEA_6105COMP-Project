// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatsComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/AttackableInterface.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CharacterCombatComponent.h"

UCharacterCombatComponent::UCharacterCombatComponent()
	:UCombatComponent()
	, m_Owner(nullptr)
	, m_bDisableMovementDuringAttack(true)
{
	//this->m_MeleeAnimationMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("AnimationMontage"));
}

void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();


	// Cast owner to ACharacter class.The owner of this component must be of class Character
	this->m_Owner = Cast<ACharacter>(this->GetOwner());

	if (!this->m_Owner)
	{
		return;
	}

	this->m_AnimatedMesh = this->m_Owner->GetMesh();
}

void UCharacterCombatComponent::AttackStart()
{
	Super::AttackStart();

	AActor* tOwner = this->GetOwner();

	// Check if the owner implements AttackableInterface. If it is and is not alive, do not continue
	if (!tOwner->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass())
		|| !IAttackableInterface::Execute_IsAlive(tOwner))
	{
		this->ResetAttack();
		return;
	}



	if (this->m_bDisableMovementDuringAttack)
	{
		// Disable Movement
		this->m_Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
}

void UCharacterCombatComponent::CustomTickComponent()
{
	Super::CustomTickComponent();
}

void UCharacterCombatComponent::PerformMeleeAttack()
{
	Super::PerformMeleeAttack();
}

void UCharacterCombatComponent::ResetAttack()
{
	Super::ResetAttack();

	if (this->m_bDisableMovementDuringAttack)
	{
		// Enable Player movement
		this->m_Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

