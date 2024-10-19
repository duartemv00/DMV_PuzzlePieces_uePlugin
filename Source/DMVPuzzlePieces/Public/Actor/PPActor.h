// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/PPInterface.h"
#include "PPActor.generated.h"

UCLASS()
class DMVPUZZLEPIECES_API APPActor : public AActor, public IPPInterface
{
	GENERATED_BODY()

public:
	APPActor();

protected:
	virtual void BeginPlay() override;
	
};
