// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAD_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate() const;

	bool OpenDoorSound=false;
	bool CloseDoorSound=true;

private:
	float initialYaw;
	float currentYaw;

	UPROPERTY(EditAnywhere)
	float openAngle=90.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;


	float DoorLastOpened=0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .5f;

	UPROPERTY(EditAnywhere)
    float DoorOpenSpeed=.8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed=2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate=nullptr;

	


	UPROPERTY(EditAnywhere)
	FRotator DoorRotation;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	
	


	 
};
