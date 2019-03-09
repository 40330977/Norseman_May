// Fill out your copyright notice in the Description page of Project Settings.

#include "drawer_constrainer.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Grabber1.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
Udrawer_constrainer::Udrawer_constrainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Udrawer_constrainer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Udrawer_constrainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector objectPos = GetOwner()->GetTransform().GetLocation();

	if (objectPos.X > closed) {
		//physicshandle->release();
		GetOwner()->SetActorLocation(FVector(closed, objectPos.Y, objectPos.Z));
		GetOwner()->GetRootComponent()->ComponentVelocity = FVector(0.0f, 0.0f, 0.0f);

	}
	if (objectPos.X < open) {
		//physicshandle->release();
		//physicshandle->ReleaseComponent();
		GetOwner()->SetActorLocation(FVector(open, objectPos.Y, objectPos.Z));
		GetOwner()->GetRootComponent()->ComponentVelocity = FVector(0.0f, 0.0f, 0.0f);
	}
}

