// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ManagerBase.h"

AManagerBase::AManagerBase()
	: m_bShouldUpdate(false)
	, m_UpdateInterval(DEFAULT_UPDATE_INTERVAL)
	, m_ClearInterval(DEFAULT_CLEAR_INTERVAL)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;
}

void AManagerBase::BeginPlay()
{
	// Setup a timer for this manager
	GetWorld()->GetTimerManager().SetTimer(this->m_ManagerTimerHandle, this, &AManagerBase::Update, m_UpdateInterval, true);

	// Pause a timer
	GetWorld()->GetTimerManager().PauseTimer(this->m_ManagerTimerHandle);
}

void AManagerBase::Tick(float DeltaTime)
{
}

void AManagerBase::Update()
{
	this->m_CurrentClearInterval += GetWorld()->GetTimerManager().GetTimerElapsed(this->m_ManagerTimerHandle);
}

void AManagerBase::Clear()
{
	this->m_CurrentClearInterval = 0.0f;
}

void AManagerBase::SetShouldUpdate(bool ShouldUpdate)
{
	if (ShouldUpdate)
	{
		this->UpdateStart();
	}
	else
	{
		this->UpdateStop();
	}

	this->m_bShouldUpdate = ShouldUpdate;
}

void AManagerBase::SetUpdateInterval(float NewUpdateInterval)
{
	GetWorld()->GetTimerManager().SetTimer(this->m_ManagerTimerHandle, this, &AManagerBase::Update, NewUpdateInterval, true);

	this->m_UpdateInterval = NewUpdateInterval;
}
