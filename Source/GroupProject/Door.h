// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	UAudioComponent* OpenSound;

	// Unlocks door
	UFUNCTION()
	void UnlockDoor();
	// Opens door
	UFUNCTION()
	void OpenDoor();

	// Amount to rotate the door
	UPROPERTY(EditAnywhere)
	float YawValue;
	// Max door rotation
	UPROPERTY(EditAnywhere)
	float EndRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Whether to rotate the door or not
	bool Rotate;

	// Wheter the lock is door or not
	bool Lock;

	// Wheter the door is opened or not
	bool Opened;

};
