// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Engine.h"

// Sets default values
ADoor::ADoor(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Door"));
	RootComponent = DoorMesh;

	OpenSound = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Open Sound"));
	OpenSound->bAutoActivate = false;

	// Door is locked and not opened at the beginning
	Lock = true;
	Opened = false;

	YawValue = 0.0f;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Rotate)
	{
		FRotator NewRotation = FRotator(0.0f, YawValue, 0.0f);
		FQuat QuatRotation = FQuat(NewRotation);
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(GetActorRotation().Yaw));
		}*/
	}

	if (GetActorRotation().Yaw < EndRotation)
	{
		Rotate = false;
		// Unlock door
		Lock = false;
		if (OpenSound->IsPlaying())
		{
			OpenSound->Stop();
		}
	}

}

// Unlocks the door
void ADoor::UnlockDoor()
{
	Rotate = true;
	DoorMesh->SetRenderCustomDepth(true);
}

// Opens the door
void ADoor::OpenDoor()
{
	if (!Opened && !Lock)
	{
		Rotate = true;
		EndRotation = -90.0f;
		Opened = true;
		OpenSound->Play();
		DoorMesh->SetRenderCustomDepth(false);
	}
}

