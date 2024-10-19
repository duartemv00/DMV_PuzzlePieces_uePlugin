// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/TriggerActor/PPCollisionTrigger.h"
#include "Components/BoxComponent.h"


APPCollisionTrigger::APPCollisionTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	ColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComponent"));
	RootComponent = ColliderComponent;
}

void APPCollisionTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Bind the dispatcher call to the collision event
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APPCollisionTrigger::CallDispatcher);
	
}

void APPCollisionTrigger::CallDispatcher(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCharacterPassingThrough.Broadcast();
}


