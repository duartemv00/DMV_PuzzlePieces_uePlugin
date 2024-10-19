// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPTriggerActor.h"
#include "PPSingleStateTrigger.generated.h"

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPSingleStateTrigger : public APPTriggerActor
{
	GENERATED_BODY()

public:
	APPSingleStateTrigger();

protected:
	virtual void BeginPlay() override;
	void Interact_Implementation() override;

	UPROPERTY(EditInstanceOnly)
	bool bOneTimeUse;
	UPROPERTY()
	bool bUsed = false;
};
