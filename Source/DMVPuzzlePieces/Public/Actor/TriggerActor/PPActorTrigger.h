// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "Interface/Interact.h"
#include "Interface/TriggerToFeedback.h"
#include "PPActorTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerUpdated);

UCLASS(NotBlueprintable)
class DMVPUZZLEPIECES_API APPActorTrigger : public APPActor, public IInteract, public ITriggerToFeedback
{
	GENERATED_BODY()

public:
	APPActorTrigger();

	FTriggerUpdated OnTriggerdUpdated;

	virtual void ActivateOwned() override;
	virtual void DeactivateOwned() override;

protected:
	virtual void BeginPlay() override;

	// List of all the Actors that will be affected when this trigger is activated
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> ControlledActors;

	UPROPERTY()
	bool bActive= false;

	UFUNCTION(BlueprintNativeEvent)
	void SendNotActive();
	
};
