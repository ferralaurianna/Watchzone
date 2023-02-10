// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
	InteractableHelpText=FString("Press E to interact with item");
}

int32 AInteractable::GetInteractableId()
{
	return InteractableId;
}

int32 AInteractable::GetAmount()
{
	return InteractableAmount;
}

void AInteractable::Interact()
{
	this->Destroy();
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

