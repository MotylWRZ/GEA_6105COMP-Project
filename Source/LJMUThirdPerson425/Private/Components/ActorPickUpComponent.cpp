// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActors/PickupActorBase.h"

#include "Components/ActorPickUpComponent.h"

UActorPickUpComponent::UActorPickUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UActorPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	this->OnComponentBeginOverlap.AddDynamic(this, &UActorPickUpComponent::OnPickupSphereBeginOverlap);
}

void UActorPickUpComponent::OnPickupSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickupActorBase* tPickupActor = Cast<APickupActorBase>(OtherActor);

	if (tPickupActor)
	{
		tPickupActor->OnPickedUp();
	}
}