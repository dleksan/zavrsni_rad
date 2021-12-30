// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UElevator::UElevator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UElevator::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	SetElevatorTransform();
	SetLeverLocations();
	elevatorMovementDirection = true;
	moveElevator = true;
	isUpperLeverPulled = false;
	isLowerLeverPulled = false;
	
}


// Called every frame
void UElevator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!(PressurePlate->IsOverlappingActor(ActorThatOpens)) && moveElevator == false)
	{
		moveElevator = true;
	}

	
	LiftElevator(DeltaTime);


	LowerElevator(DeltaTime);

	LowerLeverTriggerVolume->GetOverlappingActors(OUT IsLowerLeverOverlaping);
	UpperLeverTriggerVolume->GetOverlappingActors(OUT IsUpperLeverOverlaping);



	for (AActor* Actor : IsLowerLeverOverlaping)
	{
		counter++;	
	}
	
	for (AActor* Actor : IsUpperLeverOverlaping)
	{
		counter++;
	}

	//UE_LOG(LogTemp, Error, TEXT("%d"), IsLeverOverlaping.Num());
	
	if (counter > 0)
	{
			UE_LOG(LogTemp, Error, TEXT("%d"),counter);
		
		//if (IsUpperLeverOverlaping.Top()->GetActorLocation().Z== 625.f)
		if (IsUpperLeverOverlaping.Num()==1)
		{
			isUpperLeverPulled = true;
		}

		if(IsLowerLeverOverlaping.Num()==1) {

			isLowerLeverPulled = true;
		}

		
	}
	if (isLowerLeverPulled)
	{
		UE_LOG(LogTemp, Error, TEXT("Rucka je povucena"));
	}

	if (counter == 0)
	{
		isUpperLeverPulled = false;
		isLowerLeverPulled = false;
	}

	counter = 0;

	
}


void UElevator::LiftElevator(float DeltaTime)
{

	if ((PressurePlate->IsOverlappingActor(ActorThatOpens) && elevatorMovementDirection == true && moveElevator == true) || isUpperLeverPulled == true)
	{
		UE_LOG(LogTemp, Error, TEXT("Uvjet za dizanje lifta"));
		if (GetElevatorHeight() == (int)upperElevatorLocation.Z)
		{

			elevatorMovementDirection = !(elevatorMovementDirection);
			moveElevator = false;

		}

		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation;
		TargetLocation = FMath::Lerp(CurrentLocation, upperElevatorLocation, 0.01f);
		GetOwner()->SetActorLocation(TargetLocation, false, 0, ETeleportType::None);

	}
}



void UElevator::LowerElevator(float DeltaTime)
{
	if ((PressurePlate->IsOverlappingActor(ActorThatOpens) && elevatorMovementDirection == false && moveElevator == true) || isLowerLeverPulled == true)
	{
		UE_LOG(LogTemp, Error, TEXT("Uvjet za spustanje lifta"));
		if (GetElevatorHeight() == (int)lowerElevatorLocation.Z)
		{
			elevatorMovementDirection = !(elevatorMovementDirection);
			moveElevator = false;

		}

		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation;
		TargetLocation = FMath::Lerp(CurrentLocation, lowerElevatorLocation, 0.01f);
		GetOwner()->SetActorLocation(TargetLocation, false, 0, ETeleportType::None);

	}
}


void UElevator::SetElevatorTransform()
{
	lowerElevatorLocation = GetOwner()->GetActorLocation();
	lowerElevatorLocation.Z = 39.f;

	upperElevatorLocation = GetOwner()->GetActorLocation();
	upperElevatorLocation.Z = 498.f;
}


void UElevator::SetLeverLocations()
{
	LowerLeverLocation.X = 46.f;
	LowerLeverLocation.Y = 709.f;
	LowerLeverLocation.Z = 138.f;
	
	UpperLeverLocation.X = 88.f;
	UpperLeverLocation.Y = 659.f;
	UpperLeverLocation.Z = 625.f;

}


float UElevator::GetElevatorHeight()
{
	elevatorLocation = GetOwner()->GetActorLocation();
	elevatorHeight = elevatorLocation.Z;
	if ((int)elevatorLocation.Z == 497)
	{
		elevatorHeight = 498.f;
	}

	if ((int)elevatorLocation.Z == 39)
	{
		elevatorHeight = 39.f;
	}
	return elevatorHeight;
}



FVector UElevator::GetElevatorLocation()
{
	return GetOwner()->GetActorLocation();
}





