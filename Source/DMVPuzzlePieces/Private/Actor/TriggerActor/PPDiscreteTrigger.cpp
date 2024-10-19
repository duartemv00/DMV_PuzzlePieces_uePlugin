// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPDiscreteTrigger.h"

#include <cassert>


APPDiscreteTrigger::APPDiscreteTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPDiscreteTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Check if the configuration of the puzzle piece is correct
	assert(MinValue<MaxValue);
	assert(DefaultValue<=MaxValue && DefaultValue>=MinValue);
	CurrentValue = MinValue;

	// Check if the puzzle piece is already correct
	if(CurrentValue == ExpectedValue)
	{
		SendPieceHasCorrectValue();
	}
}

void APPDiscreteTrigger::Interact_Implementation()
{
	// Exit if the piece is not active
	if(!bActive)
	{
		NotActiveFeedback();
		return;
	}

	// Increment the value of the piece
	if(CurrentValue < MaxValue)
	{
		CurrentValue++;
	} else
	{
		CurrentValue = MinValue;
	}

	// Check if the piece has the correct value
	if(CurrentValue == ExpectedValue)
	{
		SendPieceHasCorrectValue();
	}

	// Exit if there is no actor connected to the piece
	if(ControlledActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors connected to the trigger"));
		return;
	}

	// Send the new value to all connected actors
	for (AActor* Actor : ControlledActors)
	{
		if(Actor->GetClass()->ImplementsInterface(UPPInterface::StaticClass())) // Cast the actor to the interface
		{
			Execute_SendIntNumericValue(Actor, CurrentValue);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("No controlled actors implements the interface"));
		}
	}
}
