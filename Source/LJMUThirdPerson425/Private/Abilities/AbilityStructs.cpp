// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Ability_AOE.h"
#include "Abilities/Ability_Self.h"
#include "Abilities/Ability_Targeted.h"
//
#include "Abilities/AbilityStructs.h"

// Setup default values for AbilityStructs 

FAbilityStruct::FAbilityStruct()
{

}

FAbilityStruct_AOE::FAbilityStruct_AOE()
{
	this->AbilityAOEClass = AAbility_AOE::StaticClass();
}

FAbilityStruct_Self::FAbilityStruct_Self()
{
	this->AbilitySelfClass = AAbility_Self::StaticClass();
}

FAbilityStruct_Targeted::FAbilityStruct_Targeted()
{
	this->AbilityTargetedClass = AAbility_Targeted::StaticClass();
}