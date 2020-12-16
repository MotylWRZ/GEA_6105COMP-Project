// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/CanHasEffectsInterface.h"
#include "Interfaces/AttackableInterface.h"


#include "Utilities/General/HelperFunctionsLibrary.h"

bool UHelperFunctionsLibrary::IsActorAttackable(UPARAM(ref)AActor*& Actor)
{
    return Actor->GetClass()->ImplementsInterface(UAttackableInterface::StaticClass());
}

bool UHelperFunctionsLibrary::CanActorHasEffects(UPARAM(ref)AActor*& Actor)
{
    return Actor->GetClass()->ImplementsInterface(UCanHasEffectsInterface::StaticClass());
}
