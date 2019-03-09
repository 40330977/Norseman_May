// Fill out your copyright notice in the Description page of Project Settings.

#include "TheNorsemanGameModeBase.h"
#include "DetectiveCharacter.h"
#include "DetectiveCharacter_HUD.h"
#include "GroupProjectHUD.h"

ATheNorsemanGameModeBase::ATheNorsemanGameModeBase(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
	DefaultPawnClass = ADetectiveCharacter::StaticClass();

	HUDClass = ADetectiveCharacter_HUD::StaticClass();
}
