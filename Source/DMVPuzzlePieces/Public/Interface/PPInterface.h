// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PPInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMVPUZZLEPIECES_API IPPInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// virtual void Interact() = 0;

	// Function to communicate the player with the puzzle pieces
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PuzzlePieces")
	void Interact();
	
	// Activate related functionality in the Actors connected to the puzzle pieces (SingleState & Toggle)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void Activate();

	// Deactivate related functionality in the Actors connected to the puzzle pieces (Toggle)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void Deactivate();

	// Send the numeric value of the trigger to the conected actors (Discrete)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void SendIntNumericValue(int Value);
	
	// Send the numeric value of the trigger to the conected actors (Continuous)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void SendFloatNumericValue(float Value);

	// Communication between puzzle pieces and the manager
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void OneHasCorrectValue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	bool CheckState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	void InitializeManager();
	
	// TODO: Check why these are used.
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PuzzlePieces")
	bool TransferValue(int Value);
};
