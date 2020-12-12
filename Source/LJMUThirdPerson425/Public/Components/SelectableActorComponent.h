// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectableActorComponent.generated.h"

/* Stencil index mapping to PP_OutlineColored */
#define STENCIL_FRIENDLY_OUTLINE 1;
#define STENCIL_ENEMY_OUTLINE 2;


class UDecalComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorUnselected);

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
	void ToggleIsHovered(bool IsHovered, AActor* HoveringActor);
	UFUNCTION(BlueprintCallable)
	void ToggleIsSelected(bool IsSelected, AActor* SelectingActor);

	/*UFUNCTION(BlueprintCallable)
	void SetDecalComponent(UDecalComponent* DecalComponent) { this->m_OwnerHoverDecalComponent = DecalComponent; }*/

	UFUNCTION(BlueprintCallable)
	// Set meshes that will be outlined OnHovered and OnSelected events
	void SetHighlightableMeshes(TArray<UStaticMeshComponent*> StaticMeshComponents, TArray<USkeletalMeshComponent*> SkeletalMeshComponents);
	UFUNCTION(BlueprintCallable)
	void AddHighlightableStaticMesh(UStaticMeshComponent* StaticMeshComponent);
	UFUNCTION(BlueprintCallable)
	void AddHighlightableSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComponent);
	UFUNCTION(BlueprintCallable)
	void RemoveHighlightableStaticMesh(UStaticMeshComponent* StaticMeshComponent);
	UFUNCTION(BlueprintCallable)
	void RemoveHighlightableSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComponent);
	//////////////////
	// Getters/Setters
	//////////////////
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsActorHovered() { return this->m_bIsHovered; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsActorSelected() { return this->m_bIsSelected; }

	UFUNCTION(BlueprintCallable, Category = "SelectableComponent")
	static USelectableActorComponent* GetSelectableActorComponent(AActor* FromActor);

	UFUNCTION(BlueprintCallable)
	void OnHovered(AActor* HoveringActor);
	UFUNCTION(BlueprintCallable)
	void OnUnhovered();
	UFUNCTION(BlueprintCallable)
	void OnSelected(AActor* SelectingActor);
	UFUNCTION(BlueprintCallable)
	void OnUnselected();

	//////////////////
	// Delegates
	//////////////////
	UPROPERTY(BlueprintAssignable, Category = "SelectableActorComponent")
	FOnActorHovered OnActorHovered;
	UPROPERTY(BlueprintAssignable, Category = "SelectableActorComponent")
	FOnActorUnhovered OnActorunhovered;
	UPROPERTY(BlueprintAssignable, Category = "SelectableActorComponent")
	FOnActorSelected OnActorSelected;
	UPROPERTY(BlueprintAssignable, Category = "SelectableActorComponent")
	FOnActorUnselected OnActorUnselected;

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
	TArray<UStaticMeshComponent*> m_StaticMeshComponents;
	TArray<USkeletalMeshComponent*> m_SkeletalMeshComponents;
	bool m_bIsHovered;
	bool m_bIsSelected;
};
