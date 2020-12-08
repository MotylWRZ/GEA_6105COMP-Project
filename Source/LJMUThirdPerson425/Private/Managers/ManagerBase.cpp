// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ManagerBase.h"

UManagerBase::UManagerBase()
	: m_bShouldUpdate(false)
	, m_CurrentClearInterval(0.0f)
	, m_CurrentUpdateInterval(0.0f)
	, m_UpdateInterval(DEFAULT_UPDATE_INTERVAL)
	, m_ClearInterval(DEFAULT_CLEAR_INTERVAL)
{
}


void UManagerBase::Tick(float DeltaTime)
{
	this->m_CurrentClearInterval += DeltaTime;
	this->m_CurrentUpdateInterval += DeltaTime;

	if (this->m_CurrentUpdateInterval < this->m_UpdateInterval)
	{
		return;
	}

	this->Update(this->m_CurrentUpdateInterval);

}

void UManagerBase::Update(float DeltaTime)
{
	this->m_CurrentUpdateInterval = 0.0f;
}

void UManagerBase::Clear()
{
	this->m_CurrentClearInterval = 0.0f;
}

bool UManagerBase::IsTickable() const
{
	return this->m_bShouldUpdate;
}

void UManagerBase::SetShouldUpdate(bool ShouldUpdate)
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

void UManagerBase::SetUpdateInterval(float NewUpdateInterval)
{
	this->m_UpdateInterval = NewUpdateInterval;
}
