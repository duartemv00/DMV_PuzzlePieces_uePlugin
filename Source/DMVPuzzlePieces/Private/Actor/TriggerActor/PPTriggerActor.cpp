// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPTriggerActor.h"


APPTriggerActor::APPTriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void APPTriggerActor::BeginPlay()
{
	Super::BeginPlay();

	// Set the initial state of the trigger (active or not)
	if(bStartActive){ bActive = true; }
	else { bActive = false; }
	
}

/*
 * ACTIVATE the puzzle piece when the puzzle BEGINS.
 */
void APPTriggerActor::Activate_Implementation()
{
	bActive = true;
}

/*
 * DEACTIVATE the puzzle piece when the puzzle ENDS.
 */
void APPTriggerActor::Deactivate_Implementation()
{
	bActive = false;
}

bool APPTriggerActor::CheckState_Implementation()
{
	return bValueMatch;
}

void APPTriggerActor::SendPieceHasCorrectValue()
{
	OnPieceHasCorrectValue.Broadcast();
}

void APPTriggerActor::NotActiveFeedback_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("The trigger is not active"));
}

