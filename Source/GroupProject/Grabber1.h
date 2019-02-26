// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber1.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPPROJECT_API UGrabber1 : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber1();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void release();
	void Grab();
private:

	float reach = 100.f;
	UPhysicsHandleComponent* physicshandle = nullptr;
	UInputComponent* PlayerInputComponent /*= nullptr*/;
	

	void findphysicshandlercomponent();
	void findinputcomponent();
	const FHitResult getfirstphysicsbodyinreach();
	//ADetectiveCharacter* OwnerCharacter;
};
