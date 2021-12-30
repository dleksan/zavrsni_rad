// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElevatorLever.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAD_API UElevatorLever : public UActorComponent
{
	GENERATED_BODY()


private:
	float currentRoll;
	float initialRoll;
	float pulledRoll;
	bool isLeverPulled;
	bool isLeverDown;
	FRotator LeverRotation;


public:	
	// Sets default values for this component's properties
	UElevatorLever();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
