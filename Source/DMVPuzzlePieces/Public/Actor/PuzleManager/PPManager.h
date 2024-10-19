// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Actor/TriggerActor/PPTriggerActor.h"
#include "PPManager.generated.h"

UCLASS()
class DMVPUZZLEPIECES_API APPManager : public APPActor
{
	GENERATED_BODY()

public:
	APPManager();

protected:
	virtual void BeginPlay() override;
	
	void InitializeManager_Implementation() override;

	UFUNCTION()
	void UpdatePuzzleState();
	
	UPROPERTY(EditInstanceOnly)
	TArray<APPTriggerActor*> PuzzleComponents;

	UPROPERTY(EditInstanceOnly)
	bool bBlockPuzzleOnFinished;
	
	UPROPERTY(EditInstanceOnly)
	bool bHasOwnerManager;
	UPROPERTY(EditInstanceOnly, meta=(EditCondition="bHasOwnerManager"))
	TArray<APPManager*> OwnerManagers;
	UPROPERTY(EditInstanceOnly, meta=(EditCondition="!bHasOwnerManager"))
	TArray<APPManager*> NextStepManagers;
	
	
};
