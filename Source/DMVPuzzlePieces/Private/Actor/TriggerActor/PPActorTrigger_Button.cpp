// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPActorTrigger_Button.h"

#include <cassert>


APPActorTrigger_Button::APPActorTrigger_Button()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPActorTrigger_Button::BeginPlay()
{
	Super::BeginPlay();

	// Check if the configuration of the puzzle piece is correct
	assert(MinValue<MaxValue);
	assert(DefaultValue<=MaxValue && DefaultValue>=MinValue);

	// Set the initial current value of the piece
	CurrentValue = DefaultValue;

	// Check if the puzzle piece is already correct
	OnTriggerdUpdated.Broadcast();
}

void APPActorTrigger_Button::Interact_Implementation()
{
	// Exit if the piece is not active
	if(!bActive)
	{
		SendNotActive();
		return;
	}
	
	// Increment the value of the piece
	CurrentValue++;
	if(CurrentValue > MaxValue) {
		CurrentValue = MinValue;
	}
	
	// Communication with Manager
	OnTriggerdUpdated.Broadcast(); 
	
	// BEGIN - Feedback to Connected Actors
	if(ControlledActors.Num() == 0) // Exit if there is no actor connected to the piece
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors controlled by this trigger"));
		return;
	}
	for (AActor* Actor : ControlledActors) // Send the new value to all connected actors
	{
		if(Actor->GetClass()->ImplementsInterface(UPPInterface::StaticClass())) // Cast the actor to the interface
		{
			Execute_SendValue(Actor, CurrentValue);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("No controlled actors implements the interface"));
		}
	}
	// END - Feedback to Connected Actors
}

// NotActiveFeedback_Implementation() is not implemented in this class, but can be implemented in BP