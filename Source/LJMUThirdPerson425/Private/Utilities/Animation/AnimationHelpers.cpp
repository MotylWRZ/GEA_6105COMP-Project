// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/Animation/AnimationHelpers.h"

void UAnimationHelpers::PlayAnimMontageSection(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, int32 AnimSectionIndex, float InRate)
{
	if (!MontageToPlay)
	{
		return;
	}

	//this->AdjustAnimMontagePlayRate(MontageToPlay, tSectionIndex);
	SkeletalMeshComp->GetAnimInstance()->Montage_Play(MontageToPlay, InRate);
	SkeletalMeshComp->GetAnimInstance()->Montage_JumpToSection(MontageToPlay->GetSectionName(AnimSectionIndex));
}

void UAnimationHelpers::PlayAnimMontageSectionWithLenght(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, int32 AnimSectionIndex, float SectionLengthMax, float SectionLengthMin, float DefautPlayRate)
{
	float tCurrSectionLenght = MontageToPlay->GetSectionLength(AnimSectionIndex);
	float tRate = DefautPlayRate;

	if (tCurrSectionLenght < SectionLengthMin)
	{
		// Calculate the AnimPlayrate by the current Section(tSectionIndex)
		tRate = UAnimationHelpers::GetAdjustedMontagePlayrateBySection(MontageToPlay, AnimSectionIndex, SectionLengthMin);
	}
	if (tCurrSectionLenght > SectionLengthMax)
	{
		// Calculate the AnimPlayrate by the current Section(tSectionIndex)
		tRate = UAnimationHelpers::GetAdjustedMontagePlayrateBySection(MontageToPlay, AnimSectionIndex, SectionLengthMax);
	}

	// Play AnimMontage Section with adjusted rate
	UAnimationHelpers::PlayAnimMontageSection(MontageToPlay, SkeletalMeshComp, AnimSectionIndex, tRate);
}

void UAnimationHelpers::PlayMontageRandomly(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, float InRate)
{
	//Generate random section from the AnimMontage
	int32 tSectionIndex = FMath::RandRange(0, MontageToPlay->CompositeSections.Num() - 1);

	UAnimationHelpers::PlayAnimMontageSection(MontageToPlay, SkeletalMeshComp, tSectionIndex, InRate);
}

void UAnimationHelpers::PlayMontageRandomlyWithLength(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, float SectionLengthMax, float SectionLengthMin, float DefautPlayRate)
{
	if (!MontageToPlay)
	{
		return;
	}

	//Generate random section from the AnimMontage
	int32 tSectionIndex = UAnimationHelpers::GetRandomSectionIndexFromMontage(MontageToPlay);

	float tCurrSectionLenght = MontageToPlay->GetSectionLength(tSectionIndex);

	float tRate = DefautPlayRate;

	if (tCurrSectionLenght < SectionLengthMin)
	{
		// Calculate the AnimPlayrate by the current Section(tSectionIndex)
	    tRate = UAnimationHelpers::GetAdjustedMontagePlayrateBySection(MontageToPlay, tSectionIndex, SectionLengthMin);
	}
	if (tCurrSectionLenght > SectionLengthMax)
	{
		// Calculate the AnimPlayrate by the current Section(tSectionIndex)
		tRate = UAnimationHelpers::GetAdjustedMontagePlayrateBySection(MontageToPlay, tSectionIndex, SectionLengthMax);
	}

	// Play AnimMontage Section with adjusted rate
	UAnimationHelpers::PlayAnimMontageSection(MontageToPlay, SkeletalMeshComp, tSectionIndex, tRate);
}

float UAnimationHelpers::GetAdjustedMontagePlayrateBySection(UPARAM(ref) UAnimMontage*& MontageToPlay, int32 SectionIndex, float TargetSectionLenght)
{
	// Get the lenght of the AnimSection
	float tCurrentSectionLenght = MontageToPlay->GetSectionLength(SectionIndex);
	float tTargetSectionLenght = TargetSectionLenght;

	// Calculate the new AnimMontage PlayRate
	float tNewAnimMontagePlayRate = tCurrentSectionLenght / tTargetSectionLenght;

	return tNewAnimMontagePlayRate;
}