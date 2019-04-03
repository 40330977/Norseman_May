// Fill out your copyright notice in the Description page of Project Settings.

#include "Safescreen1.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASafescreen1::ASafescreen1(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Screen1 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Screen1"));
	RootComponent = Screen1;
	Completed = false;
	Correct = false;
	CurrentPassword = "";
	keycheck = false;
	

}

// Called when the game starts or when spawned
void ASafescreen1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASafescreen1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector keypos = key->GetActorLocation();
	if (keypos.X > xmin && keypos.X<xmax && keypos.Y > ymin && keypos.Y < ymax && keypos.Z > zmin && keypos.Z < zmax)
	{
		keycheck = true;
		UE_LOG(LogTemp, Warning, TEXT("Goal! \n"));
	}
	else
	{
		keycheck = false;
	}

}

// Adds a number to the password sequence
void ASafescreen1::AddNumber(int32 number)
{
	ClickSound();
	if (!Completed)
	{
		// Add number to current password
		CurrentPassword.AppendInt(number);
		// Print password in the screen
		PrintNumber(false, number, CurrentPassword.Len() - 1);
		if (CurrentPassword.Len() == CorrectPassword.Len())
		{
			Completed = true;
		}
	}
}

// Checks if the password entered is correct
void ASafescreen1::EnterPressed()
{
	ClickSound();

	//CardRead();

	//AActor* key;

	//FName tagger = "Key";

	//TArray<AActor*> card;

	//Trigger->GetOverlappingActors(card, TSubclassOf<AActor>());

	//for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//{
	//	// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
	//	//AStaticMeshActor *Mesh = *ActorItr;
	//	ActorItr->GetComponentsByTag()
	//	if (ActorItr->GetName() == "Cube3_5")
	//	{
	//		key = *ActorItr;
	//	}
	//	//ClientMessage(ActorItr->GetActorLocation().ToString());
	//}

	

	if (!Correct)
	{
		
		if (CurrentPassword == CorrectPassword && keycheck == true)
		{
			Correct = true;
			CorrectAnswerSound();
			Door->UnlockDoor();
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

// Deletes last digit from current password
void ASafescreen1::DeletePressed()
{
	ClickSound();
	if (!Correct && CurrentPassword.Len() > 0)
	{
		// Delete last digit
		CurrentPassword.RemoveAt(CurrentPassword.Len() - 1);
		Delete(CurrentPassword.Len());
		Completed = false;
	}
}
