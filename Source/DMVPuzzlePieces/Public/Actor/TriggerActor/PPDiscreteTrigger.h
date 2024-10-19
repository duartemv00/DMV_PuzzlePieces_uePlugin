// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPTriggerActor.h"
#include "PPDiscreteTrigger.generated.h"

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPDiscreteTrigger : public APPTriggerActor
{
	GENERATED_BODY()

public:
	APPDiscreteTrigger();

protected:
	virtual void BeginPlay() override;
	void Interact_Implementation() override;

private:
	UPROPERTY()
	int CurrentValue;
	UPROPERTY(EditInstanceOnly)
	int MaxValue;
	UPROPERTY(EditInstanceOnly)
	int MinValue;
	UPROPERTY(EditInstanceOnly)
	int DefaultValue;
	UPROPERTY(EditInstanceOnly)
	int ExpectedValue;
	
};
