// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MagicSpheres/MagicSphereTypes.h"
#include "../Abilities/Ability.h"

#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"


USTRUCT(Blueprintable)
struct FSpellStruct : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCustomiseSpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bCustomiseSpell"))
		TSubclassOf<ASpell> SpellClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		FName SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		FText SpellDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		UTexture2D* SpellIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		TEnumAsByte<EMagicSphereTypes> MagicSphereType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell", ClampMin = "0"))
		int32 ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell", ClampMin = "0", ClampMax = "100"))
		int32 SuccessChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		TArray<TSubclassOf<AAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseSpell"))
		bool bCustomiseAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseAbilities"))
		TArray<FAbilityStruct_AOE> Abilities_AOE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseAbilities"))
		TArray<FAbilityStruct_Self> Abilities_Self;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "bCustomiseAbilities"))
	int32 SpellID;

};


UCLASS()
class LJMUTHIRDPERSON425_API ASpell : public AInfo
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpell();

	UFUNCTION(BlueprintCallable)
	virtual void Initialise(FSpellStruct SpellStruct) { m_SpellStruct = SpellStruct; }
	UFUNCTION(BlueprintCallable)
	virtual bool CastSpell(AActor* CasterRef);

	FORCEINLINE bool IsSpellActive() { return m_bIsActive; }
	virtual void AutoDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UseAbilities();

	virtual void ClearInActiveAbility(AAbility* InActiveAbility);
	// Checki the Spell should be casted based on the SuccessChance
	FORCEINLINE bool ShouldCast() { return FMath::RandRange(1, 100) <= m_SpellStruct.SuccessChance ? true : false; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void UseAbility(AAbility* Ability);


	// Class Members
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpellStruct m_SpellStruct;
	USceneComponent* m_RootComponent;
	TMap<AAbility*, AAbility*> m_ActiveAbilities;
	AActor* m_Caster;
	bool m_bIsActive;
};
