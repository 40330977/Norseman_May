// Fill out your copyright notice in the Description page of Project Settings.

#include "TheNorsemanGameModeBase.h"
#include "DetectiveCharacter.h"

ATheNorsemanGameModeBase::ATheNorsemanGameModeBase(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
	DefaultPawnClass = ADetectiveCharacter::StaticClass();
}
