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
	// It will throw an error if T(Target class) is not derived from U(Instance of base class)
	template<typename T, typename U>
	static T* CastToDerived(U* Base)
	{
			static_assert(TIsDerivedFrom<T, U>::IsDerived, "Type T has to be derived from U.");
			return static_cast<T*>(Base);
	}

};
