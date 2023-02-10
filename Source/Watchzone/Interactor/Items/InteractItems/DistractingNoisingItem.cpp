// Fill out your copyright notice in the Description page of Project Settings.


#include "DistractingNoisingItem.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Kismet/GameplayStatics.h"

ADistractingNoisingItem::ADistractingNoisingItem()
{
	InteractableId=0;
}

float ADistractingNoisingItem::GetSpeed()
{
	return Speed;
}
