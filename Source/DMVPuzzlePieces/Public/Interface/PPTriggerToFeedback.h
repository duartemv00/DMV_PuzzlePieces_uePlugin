// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PPTriggerToFeedback.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPPTriggerToFeedback : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMVPUZZLEPIECES_API IPPTriggerToFeedback
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void SendValue(int Value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void NotActive();
};
