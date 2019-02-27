// Fill out your copyright notice in the Description page of Project Settings.

#include "PushButton.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework//Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
APushButton::APushButton(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Button"));
	RootComponent = ButtonMesh;
	Countdown = 0.8f;
}

// Called when the game starts or when spawned
void APushButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Countdown -= DeltaTime;
	if (Countdown < 0.0f)
	{
		if (Pushed)
		{
			FVector meshLocation = ButtonMesh->GetRelativeTransform().GetLocation();
			meshLocation.X -= 20;
			ButtonMesh->SetRelativeLocation(meshLocation);
			Pushed = false;
		}
		Countdown = 0.8f;
	}

}

void APushButton::Push()
{
	if (!Pushed)
	{
		FVector meshLocation = ButtonMesh->GetRelativeTransform().GetLocation();
		meshLocation.X += 20;
		ButtonMesh->SetRelativeLocation(meshLocation);
		Pushed = true;
		Screen->AddNumber(Number);
	}
}

