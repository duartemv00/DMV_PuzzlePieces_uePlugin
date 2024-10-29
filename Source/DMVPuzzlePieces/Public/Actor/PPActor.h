// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/PPManagerToTrigger.h"
#include "PPActor.generated.h"

UCLASS()
class DMVPUZZLEPIECES_API APPActor : public AActor, public IPPManagerToTrigger
{
	GENERATED_BODY()

public:
	// BEGIN - Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTextRenderComponent* TextComponent;
	// END - Components
	
	APPActor();

	// BEGIN - Getters
	UTextRenderComponent* GetTextComponent() const { return TextComponent; }
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	// END - Getters

	// BEGIN - Setters
	void SetTextComponent(const FString NewText) const { TextComponent->Text = FText::FromString(NewText); }
	// END - Setters

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditInstanceOnly)
	FText CustomTooltip;
	
};
