// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(LogGeneral, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(LogGameInit, Log, All);

//Logging for AI system
DECLARE_LOG_CATEGORY_EXTERN(LogGameAI, Log, All);

//Logging for a Ability System
DECLARE_LOG_CATEGORY_EXTERN(LogAbilitySystem, Log, All);

//Logging for a Spell System
DECLARE_LOG_CATEGORY_EXTERN(LogSpellSystem, Log, All);

//Logging for a Spellbook System
DECLARE_LOG_CATEGORY_EXTERN(LogSpellbookSystem, Log, All);

//Logging for a SelectableSystem
DECLARE_LOG_CATEGORY_EXTERN(LogSelectableSystem, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(LogMyGameCriticalErrors, Log, All);
