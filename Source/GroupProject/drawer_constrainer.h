// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grabber1.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "drawer_constrainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPPROJECT_API Udrawer_constrainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Udrawer_constrainer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AActor* ActorThatOpens;
	float objectPos;
	float open = -777.25f;
	float closed = -692.25f;
	UGrabber1* physicshandle = nullptr;
		
};
