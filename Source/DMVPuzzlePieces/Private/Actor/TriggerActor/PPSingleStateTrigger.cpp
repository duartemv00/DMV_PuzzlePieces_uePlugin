// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/TriggerActor/PPSingleStateTrigger.h"


APPSingleStateTrigger::APPSingleStateTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPSingleStateTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void APPSingleStateTrigger::Interact_Implementation()
{
	Super::Interact_Implementation();
	for (AActor* Actor : ControlledActors)
	{
		// if(Actor->Implements<IPPInterface>()) // Check if the actor implements the interface
		// {
		// 	Activate(); // Activate the actor through the interface
		// }
		if(Actor->GetClass()->ImplementsInterface(UPPInterface::StaticClass())) // Cast the actor to the interface
		{
			if(bOneTimeUse && bUsed)
			{
				return;
			}
			Execute_Activate(Actor); // Activate the actor through the interface
			bUsed = true;
		}
	}
}

