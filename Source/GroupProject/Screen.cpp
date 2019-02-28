// Fill out your copyright notice in the Description page of Project Settings.

#include "Screen.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AScreen::AScreen(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Screen = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Screen"));
	RootComponent = Screen;
	Completed = false;
}

// Called when the game starts or when spawned
void AScreen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Adds a number to the password sequence
void AScreen::AddNumber(int32 number)
{
	if (!Completed)
	{
		CurrentPassword.AppendInt(number);
		PrintAsterisk(false);
		if (CurrentPassword == CorrectPassword)
		{
			Completed = true;
			CorrectAnswerSound();
			// Open the door
			Door->OpenDoor();
		}
		else if (CurrentPassword.Len() == CorrectPassword.Len())
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, CurrentPassword);
			}
			// Reset the current password
			CurrentPassword = "";
			PrintAsterisk(true);
		}
	}
}

