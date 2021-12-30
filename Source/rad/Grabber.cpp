// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h" 
#include "Engine/world.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	//Checking for Physics Component
	FindPhysicsHandle();
	SetUpInputComonent();

}


void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();


	if (ActorHit)
	{
		
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetPlayersReach()

		);
	}
	

}

void UGrabber::Interact()
{
	FHitResult HitResult = GetFirstDynamicObjectInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	UE_LOG(LogTemp, Error, TEXT("OBa su palaaaaaaaa"));

	if (ActorHit)
	{
		UE_LOG(LogTemp, Error, TEXT("OBa su pala"));
		FRotator LeverRotation = ActorHit->GetActorRotation();
		LeverRotation.Roll = 91.f;
		ActorHit->SetActorRotation(LeverRotation);
		
	}


}

void UGrabber::Release()
{
	
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No physics handle component on %s"), *GetOwner()->GetName());
		//Physics if found
	}
	


}

void UGrabber::SetUpInputComonent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		InputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::Interact);

	}

}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	FHitResult hit;

	//Ray cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		GetPlayersWorldPos(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams

	);

	return hit;
}

FHitResult UGrabber::GetFirstDynamicObjectInReach() const
{

	FHitResult hit;

	//Ray cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		GetPlayersWorldPos(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams

	);

	return hit;
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;
}

FVector UGrabber::GetPlayersWorldPos() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
		
		
	}

	if (Lever)
	{
		
	}

	
}


 