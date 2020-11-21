// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"

#include "Components/CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UCharacterStatsComponent::ModifyMeleeAttack(int32 ModifyingValue)
//{
//	this->m_MeleeAttack += ModifyingValue;
//
//	if (this->m_MeleeAttack < 0)
//	{
//		this->m_MeleeAttack = 0;
//	}
//}

void UCharacterStatsComponent::ModifySpeed(int32 ModifyingValue)
{
	this->m_Speed += ModifyingValue;

	if (this->m_Speed < 0)
	{
		this->m_Speed = 0;
	}
}

void UCharacterStatsComponent::ModifyMana(int32 ModifyingValue)
{
	this->m_Mana += ModifyingValue;

	if (this->m_Mana < 0)
	{
		this->m_Mana = 0;
	}
}

