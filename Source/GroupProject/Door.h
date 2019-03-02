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

	UFUNCTION()
	void OpenDoor();

	UPROPERTY(EditAnywhere)
	float YawValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Whether to rotate the door or not
	bool Rotate;

};
