// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerActor/PPContinousTrigger.h"


APPContinousTrigger::APPContinousTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPContinousTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

