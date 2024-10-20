// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMVPUZZLEPIECES_API IInteract
{
	GENERATED_BODY()

public:
	// Function to communicate the player with the environment objects
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PuzzlePieces")
	void Interact();
};
