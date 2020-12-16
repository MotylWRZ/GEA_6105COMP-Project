// Fill out your copyright notice in the Description page of Project Settings.



#include "../../LJMUThirdPerson425.h"
#include "Characters/Heroes/Hero.h"
#include "Components/CombatComponent.h"
#include "Components/SelectableActorComponent.h"
#include "Interfaces/AttackableInterface.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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
	auto& result2 = this->InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AHeroPlayerController::MoveCharacter);
	result.bConsumeInput = false;
	result2.bConsumeInput = false;
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

	this->m_HitLocation = tHitResult.Location;

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

		USelectableActorComponent* tPreviousActorSelectedComp = USelectableActorComponent::GetSelectableActorComponent(this->m_SelectedActor);

		if (tPreviousActorSelectedComp)
		{
			tPreviousActorSelectedComp->ToggleIsSelected(false, this->GetPawn());

			this->m_SelectedActor = nullptr;
		}
	}

	// Check if the hit Actor implements the Selectable Interface
	if (this->m_HoveredActor)
	{
		USelectableActorComponent* tCurrentActorSelectedComp = USelectableActorComponent::GetSelectableActorComponent(this->m_HoveredActor);

		tCurrentActorSelectedComp->ToggleIsSelected(true, this->GetPawn());

		if (tCurrentActorSelectedComp)
		{
			// If yes, assign the pointer to it
			this->m_SelectedActor = this->m_HoveredActor;
		}
	}

	UCombatComponent* tPawnCombatComp = UCombatComponent::GetCombatComponent(this->GetPawn());

	// If player pawn has CombatComponent, try to set current selected actor as a target (even if it is nullptr)
	if (tPawnCombatComp)
	{
			tPawnCombatComp->SetTarget(this->m_SelectedActor);
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
		USelectableActorComponent* tPreviousHoveredSelectable = USelectableActorComponent::GetSelectableActorComponent(m_HoveredActor);

		tPreviousHoveredSelectable->ToggleIsHovered(false, this->GetPawn());

		this->m_HoveredActor = nullptr;
	}

	// Check if the hit Actor can be Selected (has SelectableActorComponent)
	if (HoveredActor)
	{
		USelectableActorComponent* tCurrentHoveredCSelectable = USelectableActorComponent::GetSelectableActorComponent(HoveredActor);

		if (!tCurrentHoveredCSelectable)
		{
			// return if hovered actor is not a selectable actor
			this->m_HoveredActor = nullptr;
			return;
		}

		tCurrentHoveredCSelectable->ToggleIsHovered(true, this->GetPawn());

		//Assign the pointer to it, making it a new hovered actor
		this->m_HoveredActor = HoveredActor;
	}
}

void AHeroPlayerController::MoveCharacter()
{
	APawn* tPlayerPawn = Cast<ACharacter>(this->GetPawn());

	if (!tPlayerPawn)
	{
		return;
	}

	if (this->m_HoveredActor
		&& this->m_HoveredActor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass()))
	{
		// If HoveredActor is valid, move pawn to its location
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, this->m_HoveredActor);
	}
	else
	{
		// Move pawn to mouse hit location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, this->m_HitLocation);
	}
}
