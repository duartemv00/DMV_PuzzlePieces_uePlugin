// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PPActor.h"


APPActor::APPActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetHiddenInGame(true);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(MeshComponent);
	TextComponent->SetHiddenInGame(true);
}

void APPActor::BeginPlay()
{
	Super::BeginPlay();
	
}

