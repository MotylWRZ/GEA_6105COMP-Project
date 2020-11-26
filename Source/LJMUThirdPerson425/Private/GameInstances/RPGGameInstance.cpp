// Fill out your copyright notice in the Description page of Project Settings.



#include "GameInstances/RPGGameInstance.h"

URPGGameInstance::URPGGameInstance()
{


}

void URPGGameInstance::Init()
{
	// Create an instance of SpellsManager
	this->m_SpellsManager = GetWorld()->SpawnActor<ASpellsManager>(ASpellsManager::StaticClass()); //CreateDefaultSubobject<ASpellsManager>(TEXT("SpellsManager"));
}
