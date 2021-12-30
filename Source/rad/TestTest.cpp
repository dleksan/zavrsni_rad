
// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTest.h"

// Sets default values for this component's properties
UTestTest::UTestTest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestTest::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FRotator rotator = FRotator(0.f, 45.f, 45.f);
	GetOwner()->SetActorRotation(rotator);
	
}


// Called every frame
void UTestTest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

