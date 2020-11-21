// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimationHelpers.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API UAnimationHelpers : public UObject
{
	GENERATED_BODY()
public:

		static void PlayAnimMontageSection(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, int32 AnimSectionIndex, float InRate = 1.0f);

		// Play specifiad section from the AnimMontage on the specified SkeletalMesh with dynamically adjusted Animation Length specified by TargetLenght
		// Example : TargetSectionLengthMin = 2.0f, adjust lenght for current animation if section length < 2.0f
		// Example : TargetSectionLengthMax = 1.0f, adjust length for current animation if section length > 1.0f
		static void PlayAnimMontageSectionWithLenght(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, int32 AnimSectionIndex, float SectionLengthMax, float SectionLengthMin = 0.0f, float DefautPlayRate = 1.0f);

		// Play random section from the AnimMontage on the specified SkeletalMesh with fixed Playrate
		static void PlayMontageRandomly(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, float InRate = 1.0f);

		// Play random section from the AnimMontage on the specified SkeletalMesh with dynamically adjusted Animation Length specified by TargetLenght
		// Example : TargetSectionLengthMin = 2.0f, adjust lenght for current animation if section length < 2.0f
		// Example : TargetSectionLengthMax = 1.0f, adjust length for current animation if section length > 1.0f
		static void PlayMontageRandomlyWithLength(UAnimMontage* MontageToPlay, USkeletalMeshComponent* SkeletalMeshComp, float SectionLengthMax, float SectionLengthMin = 0.0f, float DefautPlayRate = 1.0f);

		// Calculate the new AnimMontage playerate by division of specified Section length and the TargetLenght
		// This will make the whole Montage to play faster/slower depending on the section lenght and the target playrate
		static float GetAdjustedMontagePlayrateBySection(UPARAM(ref) UAnimMontage*& MontageToPlay, int32 SectionIndex, float TargetSectionLenght);

		FORCEINLINE static int32 GetRandomSectionIndexFromMontage(UPARAM(ref) UAnimMontage*& AnimMontage) { return FMath::RandRange(0, AnimMontage->CompositeSections.Num() - 1); }
};
