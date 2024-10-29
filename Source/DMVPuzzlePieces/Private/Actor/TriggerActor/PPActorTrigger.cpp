// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPActorTrigger.h"


APPActorTrigger::APPActorTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPActorTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void APPActorTrigger::ActivateOwned()
{
	bActive = true;
}

void APPActorTrigger::DeactivateOwned()
{
	bActive = false;
}

void APPActorTrigger::ResetPiece()
{
	// Reset the trigger
}

void APPActorTrigger::SendNotActive_Implementation()
{
	for (AActor* Actor : ControlledActors)
	{
		if(Actor->GetClass()->ImplementsInterface(UPPTriggerToFeedback::StaticClass()))
		{
			Execute_NotActive(Actor);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("No controlled actors implements the interface"));
		}
	}
}

