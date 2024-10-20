// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TriggerToFeedback.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTriggerToFeedback : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMVPUZZLEPIECES_API ITriggerToFeedback
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Send the numeric value of the trigger to the conected actors
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void SendValue(int Value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void NotActive();
};
