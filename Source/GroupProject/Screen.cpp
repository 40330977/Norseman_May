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
	Correct = false;
	CurrentPassword = "";
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
		// Add number to current password
		CurrentPassword.AppendInt(number);
		// Print password in the screen
		PrintNumber(false, number, CurrentPassword.Len()-1);
		if (CurrentPassword.Len() == CorrectPassword.Len())
		{
			Completed = true;
		}
	}
}

// Calls enter in blueprint
void AScreen::EnterPressed()
{
	if (!Correct)
	{
		if (CurrentPassword == CorrectPassword)
		{
			Correct = true;
			CorrectAnswerSound();
			Door->OpenDoor();
		}
		else
		{
			Completed = false;
			// Reset the current password
			CurrentPassword = "";
			PrintNumber(true, 0, 0);
		}
	}
}

// Calls delete in blueprint
void AScreen::DeletePressed()
{
	if (!Correct && CurrentPassword.Len() > 0)
	{
		// Delete last digit
		CurrentPassword.RemoveAt(CurrentPassword.Len() - 1);
		Delete(CurrentPassword.Len());
		Completed = false;
	}
}