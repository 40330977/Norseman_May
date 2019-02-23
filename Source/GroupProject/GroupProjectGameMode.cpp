// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GroupProjectGameMode.h"
#include "GroupProjectHUD.h"
#include "GroupProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGroupProjectGameMode::AGroupProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGroupProjectHUD::StaticClass();
}
