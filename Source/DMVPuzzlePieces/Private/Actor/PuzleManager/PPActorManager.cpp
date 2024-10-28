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
		bCanActivate = true;
		for (APPActorManager* Manager : ListenManagers)
		{
			bCanActivate &= Manager->CheckState();
		}
	}
	
	if(bCanActivate)
	{
		// Activate all the pieces related to the manager's puzzle
		for (TPair<APPActorTrigger*, int32> Pair : PuzzleComponents)
		{
			Pair.Key->ActivateOwned();
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

	// The new code checks the state of the puzzle when the correct answer is set in the manager
	for (TPair<APPActorTrigger*, int32> Pair : PuzzleComponents)
	{
		bPuzzleCompleted &= Pair.Key->GetCurrentValue() == Pair.Value;
	}
	
	if(bPuzzleCompleted) // If all the pieces are in the correct state
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

#if WITH_EDITOR
void APPActorManager::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APPActorManager, PuzzleName))
	{
		TextComponent->Text = PuzzleName;
	}
}
#endif
