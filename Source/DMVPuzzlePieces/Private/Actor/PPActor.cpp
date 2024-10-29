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

#if WITH_EDITOR
void APPActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);;
	
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APPActor, CustomTooltip))
	{
		TextComponent->Text = CustomTooltip;
		TextComponent->ReloadConfig();
	}
}
#endif


