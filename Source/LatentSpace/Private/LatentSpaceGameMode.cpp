// Copyright Epic Games, Inc. All Rights Reserved.

#include "LatentSpaceGameMode.h"
#include "UObject/ConstructorHelpers.h"

ALatentSpaceGameMode::ALatentSpaceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
