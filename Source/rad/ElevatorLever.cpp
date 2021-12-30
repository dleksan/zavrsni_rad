// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorLever.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UElevatorLever::UElevatorLever()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UElevatorLever::BeginPlay()
{
	Super::BeginPlay();
	
	initialRoll = GetOwner()->GetActorRotation().Roll;
	isLeverPulled = false;
	isLeverDown = false;
	pulledRoll = 40.f;
	currentRoll = 91.f;

	// ...
	
}


// Called every frame
void UElevatorLever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->GetActorRotation().Roll == 91.f)
	{
		isLeverPulled = true;
		isLeverDown = false;
	}

	if (isLeverPulled)
	{
		currentRoll = FMath::Lerp(currentRoll, pulledRoll, DeltaTime*0.7);
		//UE_LOG(LogTemp, Warning, TEXT(" %f"), currentRoll);
		LeverRotation = GetOwner()->GetActorRotation();
		LeverRotation.Roll = currentRoll;
		GetOwner()->SetActorRotation(LeverRotation);
	}

	if (int(GetOwner()->GetActorRotation().Roll) == 40)
	{
		isLeverDown = true;
		isLeverPulled = false;
	}

	if (isLeverDown)
	{
		currentRoll = FMath::Lerp(currentRoll, initialRoll, DeltaTime*0.7);
		LeverRotation = GetOwner()->GetActorRotation();
		LeverRotation.Roll = currentRoll;
		GetOwner()->SetActorRotation(LeverRotation);
	}
	
	// ...
}

