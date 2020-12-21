// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/PostProcessVolume.h"
#include "Components/DecalComponent.h"

#include "../../LJMUThirdPerson425.h"
#include "Components/ActorStatsComponent.h"

#include "Components/SelectableActorComponent.h"

// Sets default values for this component's properties
USelectableActorComponent::USelectableActorComponent()
	: m_bIsHovered(false)
	, m_bIsSelected(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USelectableActorComponent::BeginPlay()
{
	Super::BeginPlay();

		if (this->m_StaticMeshComponents.Num() == 0 || this->m_SkeletalMeshComponents.Num() == 0)
		{
			UE_LOG(LogSelectableSystem, Error, TEXT("%s has not added any static or skeletal meshes into its SelectableActorComponent. %s will not be highlighted/outlined usin the post process material."),*this->GetName(), *this->GetOwner()->GetName());
		}
}


// Called every frame
void USelectableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelectableActorComponent::ToggleIsHovered(bool IsHovered, AActor* HoveringActor)
{
	if (IsHovered)
	{
		this->OnHovered(HoveringActor);
	}
	else
	{
		this->OnUnhovered();
	}

	this->m_bIsHovered= IsHovered;
}

void USelectableActorComponent::ToggleIsSelected(bool IsSelected, AActor* SelectingActor)
{
	if (IsSelected)
	{
		this->OnSelected(SelectingActor);
	}
	else
	{
		this->OnUnselected();
	}

	this->m_bIsSelected = IsSelected;
}

void USelectableActorComponent::SetHighlightableMeshes(TArray<UStaticMeshComponent*> StaticMeshComponents, TArray<USkeletalMeshComponent*> SkeletalMeshComponents)
{
	for (auto& SMComp : StaticMeshComponents)
	{
		if (!this->m_StaticMeshComponents.Contains(SMComp) && SMComp)
		{
			this->m_StaticMeshComponents.Add(SMComp);
		}
	}

	for (auto& SKComp : SkeletalMeshComponents)
	{
		if (!this->m_SkeletalMeshComponents.Contains(SKComp) && SKComp)
		{
			this->m_SkeletalMeshComponents.Add(SKComp);
		}
	}
}

void USelectableActorComponent::AddHighlightableStaticMesh(UStaticMeshComponent* StaticMeshComponent)
{
	if (!this->m_StaticMeshComponents.Contains(StaticMeshComponent) && StaticMeshComponent)
	{
		this->m_StaticMeshComponents.Add(StaticMeshComponent);
	}
}

void USelectableActorComponent::AddHighlightableSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (!this->m_SkeletalMeshComponents.Contains(SkeletalMeshComponent) && SkeletalMeshComponent)
	{
		this->m_SkeletalMeshComponents.Add(SkeletalMeshComponent);
	}
}

void USelectableActorComponent::RemoveHighlightableStaticMesh(UStaticMeshComponent* StaticMeshComponent)
{
	if (this->m_StaticMeshComponents.Contains(StaticMeshComponent) && StaticMeshComponent)
	{
		this->m_StaticMeshComponents.Remove(StaticMeshComponent);
	}
}

void USelectableActorComponent::RemoveHighlightableSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (this->m_SkeletalMeshComponents.Contains(SkeletalMeshComponent) && SkeletalMeshComponent)
	{
		this->m_SkeletalMeshComponents.Remove(SkeletalMeshComponent);
	}
}

USelectableActorComponent* USelectableActorComponent::GetSelectableActorComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USelectableActorComponent>(FromActor->GetComponentByClass(USelectableActorComponent::StaticClass()));
	}
	return nullptr;
}

void USelectableActorComponent::OnHovered(AActor* HoveringActor)
{
	int32 tCustomStencilIndex = 0;

	if (UActorStatsComponent::IsEnemyByActor(this->GetOwner(), HoveringActor))
	{
		tCustomStencilIndex = STENCIL_ENEMY_OUTLINE;
	}
	else
	{
		UActorStatsComponent* tOwnerStats = UActorStatsComponent::GetStatsComponent(this->GetOwner());
		if(!tOwnerStats)
		{
			tCustomStencilIndex = STENCIL_NEUTRAL_OUTLINE;
		}
		else
		{
			tCustomStencilIndex = STENCIL_FRIENDLY_OUTLINE;
		}
	}

	// Enable outlinig for all stored static meshes
	for (auto& SMComp : this->m_StaticMeshComponents)
	{
		if (SMComp)
		{
			// Used by custom PostProcess to render outlines
			SMComp->SetCustomDepthStencilValue(tCustomStencilIndex);
			SMComp->SetRenderCustomDepth(true);
		}
	}

	for (auto& SKComp : this->m_SkeletalMeshComponents)
	{
		if (SKComp)
		{
			SKComp->SetCustomDepthStencilValue(tCustomStencilIndex);
			SKComp->SetRenderCustomDepth(true);
		}
	}

	this->OnActorHovered.Broadcast();
}

void USelectableActorComponent::OnUnhovered()
{
	// Disable outlinig of all stored static meshes
		for (auto& SMComp : this->m_StaticMeshComponents)
		{
			// Used by custom PostProcess to render outlines
			SMComp->SetRenderCustomDepth(false);
		}

		for (auto& SKComp : this->m_SkeletalMeshComponents)
		{
			SKComp->SetRenderCustomDepth(false);
		}


	this->OnActorunhovered.Broadcast();
}

void USelectableActorComponent::OnSelected(AActor* SelectingActor)
{
	this->OnActorSelected.Broadcast();
}

void USelectableActorComponent::OnUnselected()
{
	this->OnActorUnselected.Broadcast();
}


