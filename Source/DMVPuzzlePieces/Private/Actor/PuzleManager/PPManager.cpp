// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PuzleManager/PPManager.h"


APPManager::APPManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPManager::BeginPlay()
{
	Super::BeginPlay();

	// Bind the manager to the puzzle pieces
	for (APPTriggerActor* Piece : PuzzleComponents)
	{
		Piece->OnPieceHasCorrectValue.AddDynamic(this, &APPManager::UpdatePuzzleState);
	}
}

/*
 * Activate the Puzzle Pieces that are part of the puzzle managed by this manager.
 */
void APPManager::InitializeManager_Implementation()
{
	for (APPTriggerActor* Piece : PuzzleComponents)
	{
		Execute_Activate(Piece);
	}
}

/*
 * When one piece of the puzzle has the correct value, this function is called.
 * And checks if all the puzzle pieces are in the correct state.
 */
void APPManager::UpdatePuzzleState()
{
	bool Aux = true;
	for (APPTriggerActor* Piece : PuzzleComponents)
	{
		Aux |= !Execute_CheckState(Piece);
	}
	
	if(Aux) // If all the pieces are in the correct state
	{
		// If the manager has a next step manager
		if(NextStepManagers.Num() > 0)
		{
			for (APPManager* NextManager : NextStepManagers)
			{
				Execute_InitializeManager(NextManager);
			}
		}

		// If the manager has an owner manager
		if(OwnerManagers.Num() > 0)
		{
			for (APPManager* OwnerManager : OwnerManagers)
			{
				Execute_OneHasCorrectValue(OwnerManager);
			}
		}

		// If the manager has to block the puzzle pieces
		if(bBlockPuzzleOnFinished)
		{
			for (APPTriggerActor* Piece : PuzzleComponents)
			{
				Execute_Deactivate(Piece);
			}
		}
	}
}

