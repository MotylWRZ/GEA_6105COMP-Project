// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MagicSpheres/MagicSphere.h"
#include "../Spells/Spell.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellBookComponent.generated.h"


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


private:
	void InitialiseMagicSpheres();

public:
	// Class Members
	// Editable Spells array. Premade and custom spells can be added here in the Editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpellStruct> m_Spells;

	// Final list of spells. It is not editable and not exposed.
	TMap<int32, FSpellStruct*> m_SpellsList;

	TArray<ASpell*> m_ActiveSpells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_bUseSpellsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseSpellsDataTable"))
	UDataTable* m_SpellsDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_MagicSpheresDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EMagicSphereTypes>,FMagicSphere> m_MagicSpheres;


};
