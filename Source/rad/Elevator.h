// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"
#include "Elevator.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAD_API UElevator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UElevator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LiftElevator(float DeltaTime);
	void LowerElevator(float DeltaTime);
	void SetElevatorTransform();
	float GetElevatorHeight();
	void SetLeverLocations();
	
	FVector GetElevatorLocation();
	




private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
		FVector elevatorLocation;

	UPROPERTY(EditAnywhere)
		FVector upperElevatorLocation;

	UPROPERTY(EditAnywhere)
		FVector lowerElevatorLocation;

	float elevatorHeight;
	bool elevatorMovementDirection;
	bool moveElevator;
	bool isUpperLeverPulled;
	bool isLowerLeverPulled;
	int counter = 0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* LowerLeverTriggerVolume = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* UpperLeverTriggerVolume = nullptr;


	TArray<AActor*> IsLowerLeverOverlaping;
	TArray<AActor*> IsUpperLeverOverlaping;

	FVector LowerLeverLocation;
	FVector UpperLeverLocation;


};
