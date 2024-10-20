// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Interface/Interact.h"
#include "Interface/TriggerToFeedback.h"
#include "PPActorTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerHasCorrectValue);

UCLASS(NotBlueprintable)
class DMVPUZZLEPIECES_API APPActorTrigger : public APPActor, public IInteract, public ITriggerToFeedback
{
	GENERATED_BODY()

public:
	APPActorTrigger();

	FTriggerHasCorrectValue OnTriggerHasCorrectValue;

	virtual void ActivateOwned() override;
	virtual void DeactivateOwned() override;

	virtual bool CheckState() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SendHasCorrectValue();

	// List of all the Actors that will be affected when this trigger is activated
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> ControlledActors;

	UPROPERTY()
	bool bValueMatch = false;

	UPROPERTY()
	bool bActive= false;

	UFUNCTION(BlueprintNativeEvent)
	void SendNotActive();
	
};
