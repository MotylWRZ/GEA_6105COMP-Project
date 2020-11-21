// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DecalComponent.h"

#include "../../LJMUThirdPerson425.h"
#include "Interfaces/Selectable.h"

#include "Components/SelectableActorComponent.h"

// Sets default values for this component's properties
USelectableActorComponent::USelectableActorComponent()
	: m_OwnerHoverDecalComponent(nullptr)
	, m_OwnerSelectDecalComponent(nullptr)
	, m_bIsHovered(false)
	, m_bIsSelected(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelectableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check if owner implements the ISelectible Interface
	if (this->GetOwner()->GetClass()->ImplementsInterface(USelectable::StaticClass()))
	{
		// If it implements the interface, get the decal components
		this->m_OwnerHoverDecalComponent = ISelectable::Execute_GetHoverDecalComponent(this->GetOwner());
		this->m_OwnerSelectDecalComponent = ISelectable::Execute_GetSelectDecalComponent(this->GetOwner());

		// Check if GetSelectableCompoenent Interface function has been implemented by the component owner class
		// If it does not provide an implementation this function, display an error message
		USelectableActorComponent* tOwnerSelectbleComponentCheck = ISelectable::Execute_GetSelectableComponent(this->GetOwner());
		if (!tOwnerSelectbleComponentCheck)
		{
			UE_LOG(LogSelectableSystem, Error, TEXT("%s will not work. %s have to provide an implementation for GetSelectableComponent function."), *this->GetName(), *this->GetOwner()->GetName());
		}

		if (!m_OwnerHoverDecalComponent || !m_OwnerSelectDecalComponent)
		{
			UE_LOG(LogSelectableSystem, Error, TEXT("%s cannot work properly. %s needs to provide HoverDecal and SelecDecal components."),*this->GetName(), *this->GetOwner()->GetName());
		}
	}
	else
	{
		UE_LOG(LogSelectableSystem, Error, TEXT("%s needs to implement SelectableInterface"), *this->GetOwner()->GetName());
	}
}


// Called every frame
void USelectableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelectableActorComponent::ToggleIsHovered(bool IsHovered)
{
	if (!this->m_OwnerHoverDecalComponent)
	{
		UE_LOG(LogSelectableSystem, Error, TEXT("Decal Component cannot be NULL"));
		return;
	}

	if (IsHovered)
	{
		this->OnHovered();
	}
	else
	{
		this->OnUnhovered();
	}

	this->m_bIsHovered= IsHovered;
}

void USelectableActorComponent::ToggleIsSelected(bool IsSelected)
{
	if (!this->m_OwnerHoverDecalComponent)
	{
		UE_LOG(LogSelectableSystem, Error, TEXT("Decal Component cannot be NULL"));
		return;
	}

	if (IsSelected)
	{
		this->OnSelected();
	}
	else
	{
		this->OnUnselected();
	}

	this->m_bIsSelected = IsSelected;
}

void USelectableActorComponent::OnHovered()
{
		this->m_OwnerHoverDecalComponent->SetVisibility(true);
}

void USelectableActorComponent::OnUnhovered()
{
	this->m_OwnerHoverDecalComponent->SetVisibility(false);
}

void USelectableActorComponent::OnSelected()
{
	this->m_OwnerSelectDecalComponent->SetVisibility(true);
}

void USelectableActorComponent::OnUnselected()
{
	this->m_OwnerSelectDecalComponent->SetVisibility(false);
}


