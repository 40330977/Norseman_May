// Fill out your copyright notice in the Description page of Project Settings.

#include "PhoneScreen.h"

// Sets default values
APhoneScreen::APhoneScreen(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Screen = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Screen"));
	RootComponent = Screen;
	Completed = false;
	Correct = false;
	CurrentNumber = "";
}

// Called when the game starts or when spawned
void APhoneScreen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhoneScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Adds a number to the password sequence
void APhoneScreen::AddNumber(int32 number)
{
	ClickSound();
	if (!Completed)
	{
		// Add number to current password
		CurrentNumber.AppendInt(number);
		// Print password in the screen
		PrintNumber(false, number, CurrentNumber.Len() - 1);
		if (CurrentNumber.Len() == CorrectNumber.Len())
		{
			Completed = true;
		}
	}
}

// Checks if the password entered is correct
void APhoneScreen::CallPressed()
{
	ClickSound();
	if (!Correct)
	{
		if (CurrentNumber == CorrectNumber)
		{
			Correct = true;
			CorrectNumberSound();
		}
		else
		{
			Completed = false;
			// Reset the current password
			CurrentNumber = "";
			PrintNumber(true, 0, 0);
		}
	}
	if (Correct)
	{
		CorrectNumberSound();
	}
}

// Deletes last digit from current password
void APhoneScreen::ResetPressed()
{
	ClickSound();
	if (!Correct && CurrentNumber.Len() > 0)
	{
		// Delete all digits
		CurrentNumber = "";
		Reset();
		Completed = false;
	}
}

