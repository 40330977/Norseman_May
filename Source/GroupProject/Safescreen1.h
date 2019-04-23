// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "Engine/TriggerBox.h"
#include "Safescreen1.generated.h"

UCLASS()
class GROUPPROJECT_API ASafescreen1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASafescreen1(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
		USceneComponent* Screen1;

	UPROPERTY(EditAnywhere)
		AActor* key;

	UPROPERTY(EditAnywhere)
		int32 xmin;

	UPROPERTY(EditAnywhere)
		int32 xmax;

	UPROPERTY(EditAnywhere)
		int32 ymin;

	UPROPERTY(EditAnywhere)
		int32 ymax;

	UPROPERTY(EditAnywhere)
		int32 zmin;

	UPROPERTY(EditAnywhere)
		int32 zmax;


	UPROPERTY(EditAnywhere)
		FString CorrectPassword;

	UPROPERTY(EditAnywhere)
		ADoor* Door;

	UPROPERTY(EditAnywhere)
		ADoor* CupboardDoor;

	// Prints number in the screen
	UFUNCTION(BlueprintImplementableEvent)
		void PrintNumber(bool reset, int32 number, int32 position);

	// Delete functionality
	UFUNCTION(BlueprintImplementableEvent)
		void Delete(int32 position);

	// Plays a correct answer sound
	UFUNCTION(BlueprintImplementableEvent)
		void CorrectAnswerSound();

	// Plays a card inserted sound
	UFUNCTION(BlueprintImplementableEvent)
		void InsertedCardSound();

	// Plays a click sound
	UFUNCTION(BlueprintImplementableEvent)
		void ClickSound();

	UFUNCTION(BlueprintImplementableEvent)
		void CardRead();

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
	//if the key is in defined area
	bool keycheck;

	bool keyunlock;

	bool soundPlayed;
};
