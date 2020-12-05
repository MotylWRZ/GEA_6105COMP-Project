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
		bool bUseCompleteSpellClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseCompleteSpellClass"))
		TSubclassOf<ASpell> SpellClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass"))
		FName SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass"))
		FText SpellDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass"))
		UTexture2D* SpellIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass"))
		TEnumAsByte<EMagicSphereTypes> MagicSphereType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass", ClampMin = "0"))
		int32 ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass", ClampMin = "0", ClampMax = "100"))
		int32 SuccessChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass"))
		TArray<TSubclassOf<AAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseCompleteSpellClass", EditConditionHides))
		bool bCustomiseAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCustomiseAbilities && !bUseCompleteSpellClass", EditConditionHides))
	TArray<FAbilityStructCustomised> CustomisedAbilities;

	UPROPERTY(BlueprintReadOnly)
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
	UPROPERTY()
	USceneComponent* m_RootComponent;
	UPROPERTY()
	TMap<AAbility*, AAbility*> m_ActiveAbilities;
	UPROPERTY()
	AActor* m_Caster;
	UPROPERTY()
	bool m_bIsActive;
};
