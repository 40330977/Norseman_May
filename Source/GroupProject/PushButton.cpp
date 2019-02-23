// Fill out your copyright notice in the Description page of Project Settings.

#include "PushButton.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework//Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
APushButton::APushButton(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MyMesh"));
	RootComponent = MyMesh;
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

	static float countdown = 0.8f;
	countdown -= DeltaTime;
	if (countdown < 0.0f)
	{
		if (Pushed)
		{
			FVector meshLocation = MyMesh->GetRelativeTransform().GetLocation();
			meshLocation.X -= 20;
			MyMesh->SetRelativeLocation(meshLocation);
			Pushed = false;
		}
		countdown = 0.8f;
	}

}

void APushButton::Push()
{
	if (!Pushed)
	{
		FVector meshLocation = MyMesh->GetRelativeTransform().GetLocation();
		meshLocation.X += 20;
		MyMesh->SetRelativeLocation(meshLocation);
		Pushed = true;
	}
}

