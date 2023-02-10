// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Watchzone/Interactor/Interactable.h"
#include "DistractingNoisingItem.generated.h"

/**
 * 
 */
UCLASS()
class WATCHZONE_API ADistractingNoisingItem : public AInteractable
{
	GENERATED_BODY()
	
protected:
	ADistractingNoisingItem();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed=300;

public:
	float GetSpeed();
};
