// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectableActorComponent.generated.h"

class UDecalComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUTHIRDPERSON425_API USelectableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelectableActorComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleIsHovered(bool IsHovered);
	UFUNCTION(BlueprintCallable)
	void ToggleIsSelected(bool IsSelected);

	UFUNCTION(BlueprintCallable)
	void SetDecalComponent(UDecalComponent* DecalComponent) { this->m_OwnerHoverDecalComponent = DecalComponent; }

	//////////////////
	// Getters/Setters
	//////////////////
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsActorHovered() { return this->m_bIsHovered; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsActorSelected() { return this->m_bIsSelected; }

	UFUNCTION(BlueprintCallable)
	void OnHovered();
	UFUNCTION(BlueprintCallable)
	void OnUnhovered();
	UFUNCTION(BlueprintCallable)
	void OnSelected();
	UFUNCTION(BlueprintCallable)
	void OnUnselected();

	//////////////////
	// Private Functions
	//////////////////
private:


	//////////////////
	// Class Members
	//////////////////
private:
	UDecalComponent* m_OwnerHoverDecalComponent;
	UDecalComponent* m_OwnerSelectDecalComponent;
	bool m_bIsHovered;
	bool m_bIsSelected;
};
