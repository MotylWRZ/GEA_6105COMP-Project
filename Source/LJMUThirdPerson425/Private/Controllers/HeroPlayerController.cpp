// Fill out your copyright notice in the Description page of Project Settings.

#include "../../LJMUThirdPerson425.h"
#include "Components/SelectableActorComponent.h"
#include "Interfaces/Selectable.h"

#include "Controllers/HeroPlayerController.h"

AHeroPlayerController::AHeroPlayerController()
	:Super()
{
	this->bShowMouseCursor = true;
	this->bBlockInput = false;
	this->bEnableClickEvents = true;
	this->bEnableTouchEvents = false;
}

void AHeroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	auto& result = this->InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AHeroPlayerController::SelectHoveredActor);
	result.bConsumeInput = false;
}

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();



	GetWorld()->GetTimerManager().SetTimer(this->m_ControllerTimerHandle, this, &AHeroPlayerController::CheckForTarget, 0.01f, true);


}

void AHeroPlayerController::CheckForTarget()
{

	FHitResult tHitResult;

	FVector tWorldPos;
	FVector tWorldDir;


	DeprojectMousePositionToWorld(tWorldPos, tWorldDir);

	//tWorldDir *= 3000.0f;
	//tWorldDir += tWorldPos;

	const FName TraceTag("MyTraceTag");

	GetWorld()->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;

	GetWorld()->LineTraceSingleByChannel(tHitResult, tWorldPos, tWorldPos + tWorldDir * 10000, ECollisionChannel::ECC_Visibility, CollisionParams);

	AActor* tHitActor = tHitResult.GetActor();

	this->HoverActor(tHitActor);


}

void AHeroPlayerController::SelectHoveredActor()
{
	if (this->m_SelectedActor == this->m_HoveredActor)
	{
		return;
	}

	if (this->m_SelectedActor)
	{

		USelectableActorComponent* tPreviousActorSelectedComp = ISelectable::Execute_GetSelectableComponent(this->m_SelectedActor);

		if (tPreviousActorSelectedComp)
		{
			tPreviousActorSelectedComp->ToggleIsSelected(false);

			this->m_SelectedActor = nullptr;
		}
	}

	// Check if the hit Actor implements the Selectable Interface
	if (this->m_HoveredActor)
	{
		USelectableActorComponent* tCurrentActorSelectedComp = ISelectable::Execute_GetSelectableComponent(this->m_HoveredActor);

		tCurrentActorSelectedComp->ToggleIsSelected(true);

		if (tCurrentActorSelectedComp)
		{
			// If yes, assign the pointer to it
			this->m_SelectedActor = this->m_HoveredActor;
		}
	}
}

void AHeroPlayerController::HoverActor(AActor* HoveredActor)
{
	if (this->m_HoveredActor == HoveredActor)
	{
		return;
	}



	// Check if there is any actor currently hovered. If there is one, unhover this actor.
	// set the HoveredActor ptr to nullptr
	if (this->m_HoveredActor)
	{
		USelectableActorComponent* tPreviousHoveredSelectable = ISelectable::Execute_GetSelectableComponent(m_HoveredActor);

		tPreviousHoveredSelectable->ToggleIsHovered(false);

		this->m_HoveredActor = nullptr;
	}

	// Check if the hit Actor implements the Selectable Interface
	if (HoveredActor && HoveredActor->GetClass()->ImplementsInterface(USelectable::StaticClass()))
	{
		USelectableActorComponent* tCurrentHoveredCSelectable = ISelectable::Execute_GetSelectableComponent(HoveredActor);

		if (!tCurrentHoveredCSelectable)
		{
			UE_LOG(LogSelectableSystem, Error, TEXT("%s cannot be hovered or selected. It is Selectable but it does not provide an implementation for SelectableInterface"), *HoveredActor->GetName());
			return;
		}

		tCurrentHoveredCSelectable->ToggleIsHovered(true);

		//Assign the pointer to it, making it a new hovered actor
		this->m_HoveredActor = HoveredActor;
	}
}
