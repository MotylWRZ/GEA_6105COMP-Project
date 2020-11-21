// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Public/Components/SelectableActorComponent.h"
#include "Components/DecalComponent.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

//class UDecalComponent;
//class USelectableActorComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class LJMUTHIRDPERSON425_API ISelectable
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	 UDecalComponent* GetHoverDecalComponent();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	 UDecalComponent* GetSelectDecalComponent();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	 USelectableActorComponent* GetSelectableComponent();


};
