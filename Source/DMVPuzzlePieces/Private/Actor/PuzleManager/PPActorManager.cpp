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
		CurrentSolvingIndex = 0;
		// Activate only the first piece
		if(SolvingMethod == Sequence)
		{
			int32 CurrentIndex = 0;
			for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
			{
				if(CurrentIndex == CurrentSolvingIndex)
				{
					It->Key->ActivateOwned();
					break;
				}
				++CurrentIndex;
			}
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
				bool LastDeactivated = false;
				int32 CurrentIndex = 0;
				
				for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
				{
					if(CurrentIndex == CurrentSolvingIndex)
					{
						if (LastDeactivated) { // Iteration +1
							// Here we only enter when the value of the current trigger is the expected value,
							// to activate the next trigger (if it exists)
							bPuzzleCompleted = false; // The puzzle is not completed yet
							It->Key->ActivateOwned();
							break;
						}
						if(It->Key->GetCurrentValue() == It->Value) // Trigger value == Expected value?
						{
							// Deactivate the current trigger
							It->Key->DeactivateOwned();
							CurrentSolvingIndex++;
							LastDeactivated = true;
						} else {
							bPuzzleCompleted = false; // The puzzle is not completed yet
						}
					}
					// If we are not in the current piece, iterate one more time.
					++CurrentIndex;
				}
				break;
			}
		
		// The MANDATORY ORDER solving method is used to solve the puzzle activating the pieces in a specific order.
		case MandatoryOrder:
			{
				int32 CurrentIndex = 0;
				
				// for (auto It = PuzzleComponents.CreateIterator(); It; ++It)
				// {
				// 	if(CurrentIndex == CurrentSolvingIndex)
				// 	{
				// 		if(It->Key->GetCurrentValue() == It->Value)
				// 		{
				// 			CurrentSolvingIndex++;
				// 			break;
				// 		}
				// 		ResetPiece();
				// 		break;
				// 	}
				// 	++CurrentIndex; // If we are not in the current piece, iterate one more time.
				// }
				break;
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
