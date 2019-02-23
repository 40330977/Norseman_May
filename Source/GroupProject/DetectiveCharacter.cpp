// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectiveCharacter.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework//PlayerController.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"

// Sets default values
ADetectiveCharacter::ADetectiveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ADetectiveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADetectiveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADetectiveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &ADetectiveCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADetectiveCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADetectiveCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADetectiveCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("ClickEvent", IE_Pressed, this, &ADetectiveCharacter::ClickEvent);
}

// Move forward
void ADetectiveCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// Add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

// Move right
void ADetectiveCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0))
	{
		// Find out which way is right
		FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Ray Casting
AActor* ADetectiveCharacter::RayCast()
{
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 100.0f) + Start);

	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			return OutHit.GetActor();
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

// Click events
void ADetectiveCharacter::ClickEvent()
{
	// Returns the actor of the raycast and based on the class perform a different action
	AActor* Hit = this->RayCast();
	if (Hit != NULL)
	{
		if (Hit->GetClass()->IsChildOf(APushButton::StaticClass()))
		{
			this->PressButton();
		}
	}
}


// Press button
void ADetectiveCharacter::PressButton()
{
	class APushButton* CurrentButton = Cast<APushButton>(OutHit.GetActor());
	CurrentButton->Push();
	CurrentButton = nullptr;
}

