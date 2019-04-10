// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectiveCharacter.h"
#include "Engine/World.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework//PlayerController.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "Grabber1.h"
#include "Door.h"
#include "PhoneButton.h"

// Sets default values
ADetectiveCharacter::ADetectiveCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Foot steps sound
	FootStepsSound = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Steps Sound"));
	FootStepsSound->bAutoActivate = false;

	// Properties needed for the sound
	MovingForward = false;
	MovingSides = false;
	

	// Allow the character to crouch
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

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
	if (MovingForward || MovingSides)
	{
		if (!FootStepsSound->IsPlaying())
		{
			FootStepsSound->Play();
		}
	}
	else if (!MovingSides && !MovingForward)
	{
		if (FootStepsSound->IsPlaying())
		{
			FootStepsSound->Stop();
		}
	}
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
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADetectiveCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADetectiveCharacter::EndCrouch);
}

// Move forward
void ADetectiveCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		MovingForward = true;
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
	else
	{
		MovingForward = false;
	}

}

// Move right
void ADetectiveCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0))
	{
		MovingSides = true;
		// Find out which way is right
		FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
	else
	{
		MovingSides = false;
	}
}

// Ray Casting
AActor* ADetectiveCharacter::RayCast()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		// Get the coordinates of the mouse from our controller  
		float LocationX;
		float LocationY;
		PlayerController->GetMousePosition(LocationX, LocationY);
		// Do a trace and see if there the position intersects something in the world  
		FVector2D MousePosition(LocationX, LocationY);
		const bool bTraceComplex = false;
		if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, bTraceComplex, OutHit) == true)
		{
			if (OutHit.bBlockingHit)
			{
				return OutHit.GetActor();
			}
		}
	}
	return NULL;
	/*FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 200.0f) + Start);

	FCollisionQueryParams CollisionParams;

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
	}*/
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
		if (Hit->GetClass()->IsChildOf(ADoor::StaticClass()))
		{
			this->OpenDeskDoor();
		}
		if (Hit->GetClass()->IsChildOf(APhoneButton::StaticClass()))
		{
			this->PressPhoneButton();
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

// Opens desk door button
void ADetectiveCharacter::OpenDeskDoor()
{
	class ADoor* CurrentDoor = Cast<ADoor>(OutHit.GetActor());
	CurrentDoor->OpenDoor();
	CurrentDoor = nullptr;
}

// Press phone button
void ADetectiveCharacter::PressPhoneButton()
{
	class APhoneButton* CurrentButton = Cast<APhoneButton>(OutHit.GetActor());
	CurrentButton->Push();
	CurrentButton = nullptr;
}

// Start crouching
void ADetectiveCharacter::StartCrouch()
{
	Crouch();
}
// End crouching
void ADetectiveCharacter::EndCrouch()
{
	UnCrouch();
}
