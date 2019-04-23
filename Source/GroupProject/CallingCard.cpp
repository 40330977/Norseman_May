// Fill out your copyright notice in the Description page of Project Settings.

#include "CallingCard.h"
#include "Engine.h"

// Sets default values
ACallingCard::ACallingCard(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CardMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Card"));
	RootComponent = CardMesh;

}

// Called when the game starts or when spawned
void ACallingCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACallingCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

