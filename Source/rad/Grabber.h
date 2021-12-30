// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAD_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float reach = 130.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;


	AActor* Lever = nullptr;

	void Grab();
	void Release();
	void Interact();
	void FindPhysicsHandle();
	void SetUpInputComonent();

	// Return the first actor wtithin reach with physics body,
	FHitResult GetFirstPhysicsBodyInReach() const;


	FHitResult GetFirstDynamicObjectInReach() const;

	// Return Line Trace end 
	FVector GetPlayersReach() const;

	// Get Players Position in world
	FVector GetPlayersWorldPos() const; 



};
