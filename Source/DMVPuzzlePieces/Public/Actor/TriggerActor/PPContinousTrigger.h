// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPTriggerActor.h"
#include "PPContinousTrigger.generated.h"

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPContinousTrigger : public APPTriggerActor
{
	GENERATED_BODY()

public:
	APPContinousTrigger();

protected:
	virtual void BeginPlay() override;
	
};
