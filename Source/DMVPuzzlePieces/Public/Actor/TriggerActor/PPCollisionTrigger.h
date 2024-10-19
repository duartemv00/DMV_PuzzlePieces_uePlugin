// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPTriggerActor.h"
#include "PPCollisionTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterPassingThrough);

UCLASS(Blueprintable)
class DMVPUZZLEPIECES_API APPCollisionTrigger : public APPTriggerActor
{
	GENERATED_BODY()

public:
	APPCollisionTrigger();
	
	FCharacterPassingThrough OnCharacterPassingThrough;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* ColliderComponent;

	UFUNCTION()
	void CallDispatcher(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
