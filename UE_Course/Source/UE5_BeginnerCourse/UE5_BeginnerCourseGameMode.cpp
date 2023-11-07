// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_BeginnerCourseGameMode.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_BeginnerCourseGameMode::AUE5_BeginnerCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
