// Fill out your copyright notice in the Description page of Project Settings.

#include "PhoneButton.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APhoneButton::APhoneButton(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Button"));
	RootComponent = ButtonMesh;
	Countdown = 0.1f;
}

// Called when the game starts or when spawned
void APhoneButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhoneButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the button to its original position
	Countdown -= DeltaTime;
	if (Countdown < 0.0f)
	{
		if (Pushed)
		{
			FVector meshLocation = ButtonMesh->GetRelativeTransform().GetLocation();
			meshLocation.Z += 0.5f;
			ButtonMesh->SetRelativeLocation(meshLocation);
			Pushed = false;
		}
		Countdown = 0.1f;
	}
}

void APhoneButton::Push()
{
	if (!Pushed)
	{
		// Moves button a bit to the back
		FVector meshLocation = ButtonMesh->GetRelativeTransform().GetLocation();
		meshLocation.Z -= 0.5f;
		ButtonMesh->SetRelativeLocation(meshLocation);
		Pushed = true;
		// Intereaction depends on the type of button
		if (IsNumber)
		{
			Screen->AddNumber(Number);
		}
		else if (IsCall)
		{
			Screen->CallPressed();
		}
		else if (IsReset)
		{
			Screen->ResetPressed();
		}
	}
}

