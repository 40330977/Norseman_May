// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhoneScreen.h"
#include "PhoneButton.generated.h"

UCLASS()
class GROUPPROJECT_API APhoneButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhoneButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
	APhoneScreen* Screen;

	UPROPERTY(EditAnywhere)
	int32 Number;

	// Button Type, defines the interaction
	UPROPERTY(EditAnywhere)
	bool IsNumber;
	UPROPERTY(EditAnywhere)
	bool IsCall;
	UPROPERTY(EditAnywhere)
	bool IsReset;

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
