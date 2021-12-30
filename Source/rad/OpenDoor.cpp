// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	openAngle += initialYaw; 

	
	FindPressurePlate();
	

	FindAudioComponent();
	// ...
}

void UOpenDoor::FindAudioComponent() 
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate() const
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s hase the open door component on it, but no pressure plate set"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (TotalMassOfActors()>MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds(); 
	}

	else
	{
		if((GetWorld()->GetTimeSeconds())-DoorLastOpened>=DoorCloseDelay) 
		CloseDoor(DeltaTime);
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, openAngle, DeltaTime*DoorOpenSpeed);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;

	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
	
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime*DoorCloseSpeed );
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	OpenDoorSound = false;
	if (!AudioComponent) { return; }

	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}

	if (!CloseDoorSound)
	{
	AudioComponent->Play();
	CloseDoorSound = true;
	}

}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressureplate!"), *Actor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%f is mass"), TotalMass);

	}
    
	return TotalMass;
}

