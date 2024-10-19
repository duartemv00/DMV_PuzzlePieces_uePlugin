// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PPActor.h"
#include "PPTriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPieceHasCorrectValue);

UCLASS(NotBlueprintable)
class DMVPUZZLEPIECES_API APPTriggerActor : public APPActor
{
	GENERATED_BODY()

public:
	APPTriggerActor();

	FPieceHasCorrectValue OnPieceHasCorrectValue;

protected:
	virtual void BeginPlay() override;
	void Activate_Implementation() override;
	void Deactivate_Implementation() override;
	bool CheckState_Implementation() override;

	UFUNCTION()
	void SendPieceHasCorrectValue();

	// List of all the Actors that will be affected when this trigger is activated
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> ControlledActors;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	bool bValueMatch = false;

	UPROPERTY()
	bool bActive= true;
	UPROPERTY(EditInstanceOnly)
	bool bStartActive= true;

	UFUNCTION(BlueprintNativeEvent)
	void NotActiveFeedback();
	
};
