// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ManagerBase.generated.h"

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
	virtual void Update() {};

protected:
	void SetShouldUpdate(bool ShouldUpdate);
	FORCEINLINE bool ShouldUpdate() { return m_bShouldUpdate; }

	FORCEINLINE void UpdateStart() { GetWorld()->GetTimerManager().UnPauseTimer(m_ManagerTimerHandle); }
	FORCEINLINE void UpdateStop() { GetWorld()->GetTimerManager().PauseTimer(m_ManagerTimerHandle); }
public:

private:
	FTimerHandle m_ManagerTimerHandle;
	bool m_bShouldUpdate;
};
