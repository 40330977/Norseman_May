// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Engine.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		FRotator NewRotation = FRotator(0.0f, -YawValue, 0.0f);
		FQuat QuatRotation = FQuat(NewRotation);
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(GetActorRotation().Yaw));
		}
	}

	if (GetActorRotation().Yaw < -100.0f)
	{
		Rotate = false;
	}

}

// Opens the door
void ADoor::OpenDoor()
{
	Rotate = true;
}

