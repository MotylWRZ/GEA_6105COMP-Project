// Copyright Epic Games, Inc. All Rights Reserved.

#include "LJMUThirdPerson425GameMode.h"
#include "LJMUThirdPerson425Character.h"
#include "UObject/ConstructorHelpers.h"

ALJMUThirdPerson425GameMode::ALJMUThirdPerson425GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
