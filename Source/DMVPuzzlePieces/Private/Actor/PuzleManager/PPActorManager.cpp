// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PuzleManager/PPActorManager.h"


APPActorManager::APPActorManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPActorManager::BeginPlay()
{
	Super::BeginPlay();

	if(bCanActivate)
	{
		TryInitializeManager();
	}

	// Bind the manager to the puzzle pieces it is managing
	for (APPActorTrigger* Piece : PuzzleComponents)
	{
		Piece->OnTriggerHasCorrectValue.AddDynamic(this, &APPActorManager::UpdatePuzzleState);
	}

	// Bin the manager to the managers it is listening to
	for (APPActorManager* Manager : ListenManagers)
	{
		Manager->OnPuzzleCompleted.AddDynamic(this, &APPActorManager::TryInitializeManager);
	}
}

bool APPActorManager::CheckState()
{
	return bPuzzleCompleted;
}

/**
 * Activate the Puzzle Pieces that are part of the puzzle managed by this manager.
 */
void APPActorManager::TryInitializeManager()
{
	if(ListenManagers.Num() > 0)
	{
		bCanActivate = true;
		for (APPActorManager* Manager : ListenManagers)
		{
			bCanActivate &= Manager->CheckState();
		}
	}
	
	if(bCanActivate)
	{
		// Activate all the pieces related to the manager's puzzle
		for (APPActorTrigger* Piece : PuzzleComponents)
		{
			Piece->ActivateOwned();
		}
	}
}

/**
 * When one piece of the puzzle has the correct value, this function is called.
 * And checks if all the puzzle pieces are in the correct state.
 */
void APPActorManager::UpdatePuzzleState()
{
	bPuzzleCompleted = true;
	for (APPActorTrigger* Piece : PuzzleComponents)
	{
		bPuzzleCompleted &= Piece->CheckState();
	}
	
	if(bPuzzleCompleted) // If all the pieces are in the correct state
	{
		OnPuzzleCompleted.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Puzzle Completed"));

		// If the manager has to block the puzzle pieces
		if(bBlockPuzzleOnFinished)
		{
			for (APPActorTrigger* Piece : PuzzleComponents)
			{
				Piece->DeactivateOwned();
			}
		}
	}
}

