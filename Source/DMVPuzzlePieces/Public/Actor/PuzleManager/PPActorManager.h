// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Actor/TriggerActor/PPActorTrigger.h"
#include "PPActorManager.generated.h"

UENUM()
enum ESolvingMethod
{
	Free,
	Sequence,
	MandatoryOrder
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleCompleted);

UCLASS()
class DMVPUZZLEPIECES_API APPActorManager : public APPActor
{
	GENERATED_BODY()

public:
	APPActorManager();

	FPuzzleCompleted OnPuzzleCompleted;

protected:
	virtual void BeginPlay() override;
	virtual bool CheckState() override;

	UPROPERTY(EditInstanceOnly)
	bool bDebug = false;

	// Internal check to see if the puzzle is completed
	UPROPERTY()
	bool bPuzzleCompleted = false;

	// When the puzzle is completed, block the Trigger Actors that are part of the puzzle
	UPROPERTY(EditInstanceOnly)
	bool bBlockPuzzleOnFinished;
	
	bool bActivate = false;

	// Solving method
	UPROPERTY(EditInstanceOnly)
	TEnumAsByte<ESolvingMethod> SolvingMethod = Free;

	UPROPERTY() // This is only used for the Sequence & MandatoryOrder solving method
	int32 CurrentSolvingIndex = 0;
	
	UPROPERTY(EditInstanceOnly)
	TMap<APPActorTrigger*, int32> PuzzleComponents;
	
	UPROPERTY(EditInstanceOnly)
	TArray<APPActorManager*> ListenManagers;
	
	UFUNCTION()
	void TryInitializeManager();
	
	UFUNCTION()
	void UpdatePuzzleState();
	
};
