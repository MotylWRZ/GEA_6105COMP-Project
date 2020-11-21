// Copyright Epic Games, Inc. All Rights Reserved.

#include "LJMUThirdPerson425.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, LJMUThirdPerson425, "LJMUThirdPerson425" );

//Logging during game startup
DEFINE_LOG_CATEGORY(LogGameInit);

//Logging for AI system
DEFINE_LOG_CATEGORY(LogGameAI);

//Logging for a Ability System
DEFINE_LOG_CATEGORY(LogAbilitySystem);

//Logging for a Spell System
DEFINE_LOG_CATEGORY(LogSpellSystem);

//Logging for a Spellbook System
DEFINE_LOG_CATEGORY(LogSpellbookSystem);

//Logging for a SelectableSystem
DEFINE_LOG_CATEGORY(LogSelectableSystem);

//Logging for Critical Errors that must always be addressed
DEFINE_LOG_CATEGORY(LogMyGameCriticalErrors);