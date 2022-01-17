// Copyright Epic Games, Inc. All Rights Reserved.

#include "MystCoreGameMode.h"
#include "MystCoreHUD.h"
#include "MystCoreCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMystCoreGameMode::AMystCoreGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Characters/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMystCoreHUD::StaticClass();
}
