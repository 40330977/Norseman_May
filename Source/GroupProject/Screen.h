// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "Screen.generated.h"

UCLASS()
class AScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScreen(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	USceneComponent* Screen;

	UPROPERTY(EditAnywhere)
	FString CorrectPassword;

	UPROPERTY(EditAnywhere)
	ADoor* Door;

	// Prints number in the screen
	UFUNCTION(BlueprintImplementableEvent)
	void PrintNumber(bool reset, int32 number, int32 position);

	// Delete functionality
	UFUNCTION(BlueprintImplementableEvent)
	void Delete(int32 position);

	// Plays a correct answer sound
	UFUNCTION(BlueprintImplementableEvent)
	void CorrectAnswerSound();

	// Plays a click sound
	UFUNCTION(BlueprintImplementableEvent)
	void ClickSound();

	// Add number to password
	void AddNumber(int32 number);

	// Enter button pressed
	void EnterPressed();

	// Calls delete in blueprint
	void DeletePressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString CurrentPassword;
	// Wheter there are four numbers in the password
	bool Completed;
	// Wheter the password is complete
	bool Correct;
};
