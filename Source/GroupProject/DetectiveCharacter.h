// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PushButton.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber1.h"
#include "DetectiveCharacter.generated.h"


UCLASS()
class ADetectiveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADetectiveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Handles moving forward/backwards
	UFUNCTION()
	void MoveForward(float val);
	// Handles moving to the sides
	UFUNCTION()
	void MoveRight(float val);
	// Handles click events
	UFUNCTION()
	void ClickEvent();
	// Handles pressing buttons
	UFUNCTION()
	void PressButton();
	

private:
	// Handles ray casting
	UFUNCTION()
	AActor* RayCast();
	// The hit result
	FHitResult OutHit;
	UPhysicsHandleComponent* physicshandle = nullptr;
	UGrabber1* grabber1 = nullptr;
};
