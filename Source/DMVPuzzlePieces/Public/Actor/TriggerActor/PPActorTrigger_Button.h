// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPActorTrigger.h"
#include "PPActorTrigger_Button.generated.h"

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPActorTrigger_Button : public APPActorTrigger
{
	GENERATED_BODY()

public:
	APPActorTrigger_Button();

protected:
	virtual void BeginPlay() override;
	void Interact_Implementation() override;
	int32 GetCurrentValue() override { return CurrentValue; }

	UPROPERTY()
	int CurrentValue;
	UPROPERTY(EditInstanceOnly)
	int MaxValue;
	UPROPERTY(EditInstanceOnly)
	int MinValue;
	UPROPERTY(EditInstanceOnly)
	int DefaultValue;
};
