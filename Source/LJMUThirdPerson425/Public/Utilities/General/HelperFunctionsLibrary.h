// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Templates/UnrealTypeTraits.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HelperFunctionsLibrary.generated.h"

/**
 *
 */
UCLASS()
class LJMUTHIRDPERSON425_API UHelperFunctionsLibrary : public UObject
{
	GENERATED_BODY()

public:

	// Cast To Derived class. Useful for structs downcasting.
	// It will throw an error if T(Target class) is not derived from U(Base class)
	template<typename T, typename U>
	static T* CastToDerived(U* Base)
	{
			static_assert(TIsDerivedFrom<T, U>::IsDerived, "Type T has to be derived from U.");
			return static_cast<T*>(Base);
	}

	static bool IsActorAttackable(UPARAM(ref)AActor*& Actor);
	static bool IsActorSelectable(UPARAM(ref)AActor*& Actor);
	static bool CanActorHasEffects(UPARAM(ref)AActor*& Actor);

};
