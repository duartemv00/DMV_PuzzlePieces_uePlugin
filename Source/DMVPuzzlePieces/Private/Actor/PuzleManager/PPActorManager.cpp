// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PuzleManager/PPActorManager.h"


APPActorManager::APPActorManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPActorManager::BeginPlay()
{
	Super::BeginPlay();

	// If the manager is not listening to any other manager, it is the root manager
	if(ListenManagers.Num() == 0)
	{
		bActivate = true;
		TryInitializeManager();
	}

	// Bind the manager to the puzzle pieces it is managing
	for (TPair<APPActorTrigger*, int32> Pair : PuzzleComponents)
	{
		Pair.Key->OnTriggerdUpdated.AddDynamic(this, &APPActorManager::UpdatePuzzleState);
	}

	// Bin the manager to the managers it is listening to
	for (APPActorManager* Manager : ListenManagers)
	{
		Manager->OnPuzzleCompleted.AddDynamic(this, &APPActorManager::TryInitializeManager);
	}
}

/**
 * Check if the puzzle is completed.
 * @return True if the puzzle is completed.
 */
bool APPActorManager::CheckState() { return bPuzzleCompleted; }

/**
 * Activate the Puzzle Pieces that are part of the puzzle managed by this manager.
 */
void APPActorManager::TryInitializeManager()
{
	if(ListenManagers.Num() > 0)
	{
		bActivate = true; // Assume the manager is active
		for (APPActorManager* Manager : ListenManagers)
		{
			bActivate &= Manager->CheckState();
		}
	}

	// If the manager is active, activate the puzzle pieces
	if(bActivate)
	{
		CurrentSolvedIndex = 0;
		// Activate only the first piece
		if(SolvingMethod == Sequence)
		{
			ActivateNextPuzzlePiece();
		}
		else {
			// Activate every piece
			for (TPair<APPActorTrigger*, int32> Pair : PuzzleComponents)
			{
				Pair.Key->ActivateOwned();
			}
		}
	}
}

/**
 * When one piece of the puzzle has the correct value, this function is called.
 * And checks if all the puzzle pieces are in the correct state.
 */
void APPActorManager::UpdatePuzzleState()
{
	bPuzzleCompleted = true; // Assume the puzzle is completed
	
	// Checks if all the pieces are in the correct state
	switch (SolvingMethod)
	{
		case Free:
			for (TPair<APPActorTrigger*, int32> Pair : PuzzleComponents)
			{
				bPuzzleCompleted &= Pair.Key->GetCurrentValue() == Pair.Value;
			}
			break;

		// The SEQUENCE solving method is used to solve the puzzle activating one piece at a time.
		case Sequence:
			{
				if(CurrentSolvedIndex == PuzzleComponents.Num() - 1)
				{
					bPuzzleCompleted = true;
					break;
				}

				bool LastDeactivated = false;
				int32 CurrentIndex = 0;
				
				bPuzzleCompleted = false; // The puzzle is not completed yet
				
				for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
				{
					if(CurrentIndex == CurrentSolvedIndex)
					{
						if (LastDeactivated) {
							It->Key->ActivateOwned();
							break;
						}
						if(It->Key->GetCurrentValue() == It->Value)
						{
							if(!LastDeactivated)
							{
								It->Key->DeactivateOwned();
								CurrentSolvedIndex++;
								LastDeactivated = true;
							}
						}
					}
					++CurrentIndex;
				}
				break;
			}
		
		// The MANDATORY ORDER solving method is used to solve the puzzle activating the pieces in a specific order.
		case MandatoryOrder:
			{
				if(CurrentSolvedIndex == PuzzleComponents.Num() - 1)
				{
					bPuzzleCompleted = true;
					break;
				}

				int32 CurrentIndex = 0;
				
				bPuzzleCompleted = false; // The puzzle is not completed yet
				
				for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
				{
					if(CurrentIndex == CurrentSolvedIndex)
					{
						if(It->Key->GetCurrentValue() == It->Value)
						{
							CurrentSolvedIndex++;
							break;
						} 
						ResetPiece();
						break;
					} 
				}
			}

		// DEFAULT FOR THE IMPOSSIBLE CASE
		default:
			break;
	}

	// If all the pieces are in the correct state, the puzzle is completed
	if(bPuzzleCompleted) 
	{
		OnPuzzleCompleted.Broadcast();
		if(bDebug) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Puzzle Completed"));

		// If the manager has to block the puzzle pieces
		if(bBlockPuzzleOnFinished)
		{
			for (TPair<APPActor*, int32> Pair : PuzzleComponents)
			{
				Pair.Key->DeactivateOwned();
			}
		}
	}
}

void APPActorManager::ActivateNextPuzzlePiece()
{
	int32 CurrentIndex = 0;
	for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
	{
		if(CurrentIndex == CurrentSolvedIndex)
		{
			It->Key->ActivateOwned();
			break;
		}
		++CurrentIndex;
	}
}
