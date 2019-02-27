// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	// Prints asterisk in the screen
	UFUNCTION(BlueprintImplementableEvent)
	void PrintAsterisk(bool reset);

	// Plays a correct answer sound
	UFUNCTION(BlueprintImplementableEvent)
	void CorrectAnswerSound();

	// Add number to password
	void AddNumber(int32 number);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString CurrentPassword;
	bool Completed;
};
