// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ActorStatsComponent.h"

#include "Actors/ActorBase.h"

// Sets default values
AActorBase::AActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root component setup
	this->m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	this->RootComponent = this->m_RootComponent;

	// ActorStatsComponent setup
	this->m_ActorStatsComponent = CreateDefaultSubobject<UActorStatsComponent>(TEXT("Actor Stats Component"));
}

// Called when the game starts or when spawned
void AActorBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

