// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "DetectiveCharacter.h"
#include "Screen.h"
#include "Safescreen1.h"
#include "PushButton.generated.h"

UCLASS()
class APushButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
	AScreen* Screen;

	UPROPERTY(EditAnywhere)
		ASafescreen1* Screen1;


	UPROPERTY(EditAnywhere)
	int32 Number;
	
	// Button Type, defines the interaction
	UPROPERTY(EditAnywhere)
	bool IsNumber;
	UPROPERTY(EditAnywhere)
	bool IsEnter;
	UPROPERTY(EditAnywhere)
	bool IsDelete;

	UFUNCTION()
	void Push();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Button is pushed
	bool Pushed;

	// Countdown
	float Countdown;

};
