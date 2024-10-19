// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPToggleTrigger.h"


APPToggleTrigger::APPToggleTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPToggleTrigger::Interact_Implementation()
{
	for (AActor* Actor : ControlledActors)
	{
		// if(IPPInterface* Interface = Cast<IPPInterface>(Actor))
		if(Actor->GetClass()->ImplementsInterface(UPPInterface::StaticClass())) // Cast the actor to the interface
		{
			UE_LOG(LogTemp, Warning, TEXT("Interact_Implementation"));
			// if(Interface->CheckState()){
			// 	Interface->Deactivate(); // Deactivate the actor through the interface
			// } else
			// {
			// 	Interface->Activate(); // Activate the actor through the interface
			// }
			if(Execute_CheckState(Actor)){
				Execute_Deactivate(Actor); // Deactivate the actor through the interface
			} else
			{
				Execute_Activate(Actor); // Activate the actor through the interface
			}
			
		}
	}
}

void APPToggleTrigger::BeginPlay()
{
	Super::BeginPlay();
}
