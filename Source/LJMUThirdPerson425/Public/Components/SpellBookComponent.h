// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MagicSpheres/MagicSphere.h"
#include "../Spells/Spell.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellBookComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnManaModified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpellCast, bool, WasSuccessful);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUTHIRDPERSON425_API USpellBookComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpellBookComponent();

	UFUNCTION(BlueprintCallable)
	void CastSpell(int32 SpellID);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void LoadDataTable(UDataTable* DataTable);

	//UFUNCTION(BlueprintCallable)
	//virtual TArray<FMagicSphere> GetMagicSpheresList();

	//UFUNCTION(BlueprintCallable)
	//virtual FMagicSphere GetMagicSphere(EMagicSphereTypes SphereType);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void ModifyMana(int32 ModifyingValue);
	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void ModifyManaMax(int32 ModifyingValue);
	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void AddMana(int32 ManaToAdd);
	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void TakeMana(int32 ManaToTake);

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void ModifyManaRegenerationAmount(int32 ModifyingValue);
	UFUNCTION(BlueprintCallable, Category = "Spellbook")
		void ModifyManaRegenerationInterval(float ModifyingValue);


	///////////////////////
	// Accessors/Mutators
	///////////////////////
	UFUNCTION(BlueprintCallable, Category = "Spellbook")
	int32 const GetMana() const { return m_Mana; }

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
	int32 const GetManaMax() const { return m_ManaMax; }

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
	int32 const GetManaRegenerationAmount() const { return m_ManaRegenerationAmount; }

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
	float GetManaRegenerationInterval() const { return m_ManaRegenerationInterval; }

	UFUNCTION(BlueprintCallable, Category = "Spellbook")
	bool CanCastSpell();
	//UFUNCTION()
	/*UFUNCTION(BlueprintCallable, Category = "Spellbook")
	void SetMana(int32 NewManaAmount) {};*/

	UPROPERTY(BlueprintAssignable, Category = "Spellbook")
	FOnManaModified	 OnManaModified;
	UPROPERTY(BlueprintAssignable, Category = "Spellbook")
	FOnCooldownChange OnCooldownChange;
	UPROPERTY(BlueprintAssignable, Category = "Spellbook")
	FOnSpellCast OnSpellCast;

protected:
	void RegenerateMana();
	void ResetSpellCastCooldown();

private:
	void InitialiseMagicSpheres();
	// Override specific SpellStruct with a struct from the CompleteClass(it has to be set in the TargetSpellStruct)
	bool LoadSpellStructFromCompleteClass(FSpellStruct& TargetSpellStruct);
	void ClearCustomAbilities(FSpellStruct& TargetSpellStruct);

public:
	// Class Members
	// Editable Spells array. Premade and custom spells can be added here in the Editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpellStruct> m_Spells;

	// Final list of spells. It is not editable and not exposed.
	TMap<int32, FSpellStruct> m_SpellsList;

	TArray<ASpell*> m_ActiveSpells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_bUseSpellsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseSpellsDataTable"))
	UDataTable* m_SpellsDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_MagicSpheresDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EMagicSphereTypes>,FMagicSphere> m_MagicSpheres;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 m_Mana;
	UPROPERTY(EditDefaultsOnly)
	int32 m_ManaMax;
	UPROPERTY(EditDefaultsOnly)
	int32 m_ManaRegenerationAmount;
	UPROPERTY(EditDefaultsOnly)
	float m_ManaRegenerationInterval;
	UPROPERTY(EditDefaultsOnly)
	float m_SpellCastCooldown;

	bool m_bIsCooledDown;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTimerHandle m_SpellbookManaTimerHandle;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTimerHandle m_SpellbookCooldownTimerHandle;
};
