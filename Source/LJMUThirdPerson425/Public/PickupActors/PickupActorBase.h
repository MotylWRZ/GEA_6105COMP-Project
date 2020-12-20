// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActorBase.generated.h"

class USelectableActorComponent;

UCLASS()
class LJMUTHIRDPERSON425_API APickupActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupActorBase();

	virtual void OnPickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USelectableActorComponent* m_SelectableActorComponent;

};
