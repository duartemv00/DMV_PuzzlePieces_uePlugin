// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PPManagerToTrigger.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPPManagerToTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * This is the way Managers connect with Triggers and Owned Managers
 * and also the way Triggers connect with Actors
 * (but never vice versa)
 */
class DMVPUZZLEPIECES_API IPPManagerToTrigger
{
	GENERATED_BODY()

public:
	virtual void ActivateOwned() {};
	
	virtual void DeactivateOwned() {};

	virtual bool CheckState() { return false; };

	virtual void ResetPiece() {};
	
	virtual int32 GetCurrentValue() { return 0; };
};
