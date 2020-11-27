// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AbilitiesManager.h"

AAbilitiesManager::AAbilitiesManager()
{

}

void AAbilitiesManager::Update()
{
	AManagerBase::Update();


}

AAbility* AAbilitiesManager::CreateAbility(TSubclassOf<AAbility> AbilityClass, AActor* AbilityUser)
{
	FTransform tUserTransform = AbilityUser->GetTransform();

	AAbility* tNewAbility = GetWorld()->SpawnActor<AAbility>(AbilityClass, tUserTransform);

	if (tNewAbility)
	{
		tNewAbility->Initialise(AbilityUser);
		return tNewAbility;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Create Ability !"));
		return nullptr;
	}
	return nullptr;
}
