// Copyright Epic Games, Inc. All Rights Reserved.

#include "WatchzoneGameMode.h"
#include "WatchzoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWatchzoneGameMode::AWatchzoneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
