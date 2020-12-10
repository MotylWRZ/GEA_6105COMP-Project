// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/CanHasEffectsInterface.h"
#include "Interfaces/AttackableInterface.h"
#include "Characters/CharacterBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hero.generated.h"

class USpellBookComponent;
class UCharacterCombatComponent;

UCLASS()
class LJMUTHIRDPERSON425_API AHero : public ACharacterBase, public IAttackableInterface, public ICanHasEffectsInterface
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	AHero();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// IAttackableInterface implementation
	UFUNCTION(BlueprintCallable)
		virtual void ApplyDamage_Implementation(AActor* InstigatorActor, int32 DamageToApply) override;
	UFUNCTION(BlueprintCallable)
		virtual bool IsAlive_Implementation() override;

	// ICanHasEffectsInterface implementation
	UFUNCTION(BlueprintCallable)
	virtual bool CanEffectBeApplied_Implementation(EEffectType EffectType);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCharacterCombatComponent* m_CharacterCombatComponent;
	UPROPERTY(EditDefaultsOnly)
		USpellBookComponent* m_SpellbookComponent;
private:


};
