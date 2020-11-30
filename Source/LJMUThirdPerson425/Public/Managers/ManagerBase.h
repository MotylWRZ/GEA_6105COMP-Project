// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ManagerBase.generated.h"


const float DEFAULT_UPDATE_INTERVAL = 0.5f;
const float DEFAULT_CLEAR_INTERVAL = 5.0f;
/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API AManagerBase : public AInfo
{
	GENERATED_BODY()
public:
	AManagerBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Update();
	virtual void Clear();

protected:
	void SetShouldUpdate(bool ShouldUpdate);
	void SetUpdateInterval(float NewUpdateInterval);

	FORCEINLINE bool ShouldUpdate() { return m_bShouldUpdate; }
	FORCEINLINE float GetUpdateInterval() { return m_UpdateInterval; }

	// Reset Update interval to Default value
	FORCEINLINE void ResetUpdateInterval() { m_UpdateInterval = DEFAULT_UPDATE_INTERVAL; }
	// Reset Clear interval to Default value
	FORCEINLINE void ResetClearInterval() { m_ClearInterval = DEFAULT_CLEAR_INTERVAL; }

	// Unpause the Updating
	FORCEINLINE void UpdateStart() { GetWorld()->GetTimerManager().UnPauseTimer(m_ManagerTimerHandle); }

	// Pause the Updating
	FORCEINLINE void UpdateStop() { GetWorld()->GetTimerManager().PauseTimer(m_ManagerTimerHandle); }

	FORCEINLINE bool ShouldClear() { return m_ClearInterval <= m_CurrentClearInterval; }
public:
protected:
	FTimerHandle m_ManagerTimerHandle;
	bool m_bShouldUpdate;
	float m_UpdateInterval;
	float m_CurrentClearInterval;
	float m_ClearInterval;
private:

};
