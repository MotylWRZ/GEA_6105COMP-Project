// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCharacterStatsComponent;

UCLASS()
class LJMUTHIRDPERSON425_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function which is called prior to Character destruction
	// Implement this function in BP in order to extend the OnCharacterDestroyed() function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void CharacterBeginDestroy();
	// Override this function in child classes
	virtual void CharacterBeginDestroy_Implementation();

	// Explicitly detsroys character
	virtual void DestroyCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	// Class Members
	USceneComponent* m_RootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterStatsComponent* m_CharaterStatsComponent;
	FTimerHandle m_CharacterBaseTimerHandle;

	// Specify how long to wait before this actor will be destroyed after calling OnCharacterDestroyed function
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_DelayBeforeDestruction;
};
