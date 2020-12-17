// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CharacterStatsComponent.h"

#include "Characters/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
	:m_DelayBeforeDestruction(1.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->m_CharaterStatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("CharacterStatsComponent"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	this->m_CharaterStatsComponent->OnActorKilled.AddDynamic(this, &ACharacterBase::CharacterBeginDestroy);


}

void ACharacterBase::CharacterBeginDestroy_Implementation()
{
	// Destroy character after delay
	this->GetWorld()->GetTimerManager().SetTimer(this->m_CharacterBaseTimerHandle, this, &ACharacterBase::DestroyCharacter, this->m_DelayBeforeDestruction, false);
}

void ACharacterBase::DestroyCharacter()
{
	this->Destroy();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

