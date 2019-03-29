// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhoneScreen.generated.h"

UCLASS()
class GROUPPROJECT_API APhoneScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhoneScreen(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	USceneComponent* Screen;

	UPROPERTY(EditAnywhere)
	FString CorrectNumber;

	// Prints number in the screen
	UFUNCTION(BlueprintImplementableEvent)
	void PrintNumber(bool reset, int32 number, int32 position);

	// Delete functionality
	UFUNCTION(BlueprintImplementableEvent)
	void Reset();

	// Plays the morse code sound
	UFUNCTION(BlueprintImplementableEvent)
	void CorrectNumberSound();

	// Plays a click sound
	UFUNCTION(BlueprintImplementableEvent)
	void ClickSound();

	// Add number to password
	void AddNumber(int32 number);

	// Enter button pressed
	void CallPressed();

	// Reset button pressed
	void ResetPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString CurrentNumber;
	// Wheter there are 10 digits in the number
	bool Completed;
	// Wheter the number is complete
	bool Correct;

};
