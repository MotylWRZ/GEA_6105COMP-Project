// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SelectableActorComponent.h"

#include "PickupActors/PickupActorBase.h"

// Sets default values
APickupActorBase::APickupActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->m_SelectableActorComponent = CreateDefaultSubobject<USelectableActorComponent>(TEXT("SelectableActorComponent"));
}

void APickupActorBase::OnPickedUp()
{
}

// Called when the game starts or when spawned
void APickupActorBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickupActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

