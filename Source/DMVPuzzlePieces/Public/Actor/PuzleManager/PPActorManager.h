// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Actor/TriggerActor/PPActorTrigger.h"
#include "PPActorManager.generated.h"

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
	
	UPROPERTY(EditInstanceOnly)
	bool bBlockPuzzleOnFinished;

	UPROPERTY(EditInstanceOnly)
	bool bCanActivate = false;
	
	UPROPERTY(EditInstanceOnly)
	TMap<APPActorTrigger*, int32> PuzzleComponents;
	
	UPROPERTY(EditInstanceOnly)
	TArray<APPActorManager*> ListenManagers;
	
	UFUNCTION()
	void TryInitializeManager();
	
	UFUNCTION()
	void UpdatePuzzleState();

	bool bPuzzleCompleted = false;

private:
	// Puzzle name to show in the editor tooltip.
	UPROPERTY(EditInstanceOnly)
	FText PuzzleName;

#if WITH_EDITOR
	// TODO: Why is the PostEditChangeProperty not updating the PuzzleName correctly?
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
