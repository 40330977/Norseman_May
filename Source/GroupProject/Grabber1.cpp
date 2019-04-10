// Copyright Roderick Ewles 2019

#include "Grabber1.h"
#include "GameFramework/Actor.h"
#include "DetectiveCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Components/AudioComponent.h"


#define OUT

// Sets default values for this component's properties
UGrabber1::UGrabber1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()->GetPawn()->GetController());

	if (PlayerController) {
	PlayerController->InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab);
	PlayerController->InputComponent->BindAction("Grab", IE_Released, this, &UGrabber1::release);
	}

	
	findphysicshandlercomponent();
	
}

void UGrabber1::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed \n"));

	auto Hitresult = getfirstphysicsbodyinreach();
	auto componenttograb = Hitresult.GetComponent();
	auto actorhit = Hitresult.GetActor();
	
	if (actorhit) {
		physicshandle->GrabComponentAtLocation(
			componenttograb,
			NAME_None,
			actorhit->GetActorLocation()
			);
		audio = actorhit->FindComponentByClass<UAudioComponent>();
		if (audio != nullptr)
		{
			audio->Play();
		}
	}
}
void UGrabber1::release() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber released \n"));
	physicshandle->ReleaseComponent();
	if (audio != nullptr)
	{
		audio->Stop();
	}
}
void UGrabber1::findphysicshandlercomponent() {
	physicshandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (physicshandle)
	{

	}

	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle"), *GetOwner()->GetName());
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber test \n"));
}

void UGrabber1::findinputcomponent()
{
	
	
	PlayerInputComponent = GetOwner()->FindComponentByClass <UInputComponent>();
	if (PlayerInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("input component found"));
		PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab);
		PlayerInputComponent->BindAction("Grab", IE_Released, this, &UGrabber1::release);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber1::getfirstphysicsbodyinreach()
{

	FVector PVPL;
	FRotator PVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PVPL,
		OUT PVPR
	);

	//UE_LOG(LogTemp, Warning, TEXT("Position %s rotation %s \n"), *PVPL.ToString(), *PVPR.ToString());
	//FVector(0.f, 0.f, 70.f)
	//float reach = 100.f;
	FVector LTE = PVPL + PVPR.Vector()*reach;

	//DrawDebugLine(GetWorld(), PVPL, LTE, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PVPL,
		LTE,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit : %s \n"), *(ActorHit->GetName()));
	}

	return Hit;
}

// Called every frame
void UGrabber1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PVPL;
	FRotator PVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PVPL,
		OUT PVPR
	);

	//UE_LOG(LogTemp, Warning, TEXT("Position %s rotation %s \n"), *PVPL.ToString(), *PVPR.ToString());
	//FVector(0.f, 0.f, 70.f)
	//float reach = 100.f;
	FVector LTE = PVPL + PVPR.Vector()*reach;

	if (physicshandle->GrabbedComponent)
	{
		physicshandle->SetTargetLocation(LTE);
	}

}

