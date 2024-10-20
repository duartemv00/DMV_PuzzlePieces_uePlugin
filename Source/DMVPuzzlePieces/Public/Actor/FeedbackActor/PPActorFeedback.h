// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Interface/TriggerToFeedback.h"
#include "PPActorFeedback.generated.h"

UCLASS()
class DMVPUZZLEPIECES_API APPActorFeedback : public APPActor, public ITriggerToFeedback
{
	GENERATED_BODY()

public:
	APPActorFeedback();

protected:
	virtual void BeginPlay() override;
};
