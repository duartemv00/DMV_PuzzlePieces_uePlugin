// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPTriggerActor.h"
#include "PPToggleTrigger.generated.h"

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPToggleTrigger : public APPTriggerActor
{
	GENERATED_BODY()

public:
	APPToggleTrigger();
	void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;
};
