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

	virtual bool CheckState() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditInstanceOnly)
	bool bBlockPuzzleOnFinished;
	
	UFUNCTION()
	void TryInitializeManager();
	
	UFUNCTION()
	void UpdatePuzzleState();

	bool bPuzzleCompleted = false;
	
	UPROPERTY(EditInstanceOnly)
	bool bCanActivate = false;
	
	UPROPERTY(EditInstanceOnly)
	TArray<APPActorTrigger*> PuzzleComponents;
	
	UPROPERTY(EditInstanceOnly)
	TArray<APPActorManager*> ListenManagers;
	
};
