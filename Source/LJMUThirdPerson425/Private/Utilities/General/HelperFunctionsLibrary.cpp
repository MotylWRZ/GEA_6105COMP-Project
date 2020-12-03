// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/AttackableInterface.h"
#include "Interfaces/SelectableInterface.h"

#include "Utilities/General/HelperFunctionsLibrary.h"

bool UHelperFunctionsLibrary::IsActorAttackable(UPARAM(ref)AActor*& Actor)
{
    return Actor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass());
}

bool UHelperFunctionsLibrary::IsActorSelectable(UPARAM(ref)AActor*& Actor)
{
    return Actor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass());
}
