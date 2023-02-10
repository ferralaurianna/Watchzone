// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	int32 GetInteractableId();
	int32 GetAmount();
	
	void Interact();
	
	void Use();
	
	/*Every interactable must have a mesh*/
	UPROPERTY(EditAnywhere,Category="Interactable Properties")
	class UStaticMeshComponent* InteractableMesh;

	/*Every interactable must have a help text for the player*/
	UPROPERTY(EditAnywhere,Category="Interactable Properties")
	FString InteractableHelpText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Interactable Properties")
	int32 InteractableId=0;

	UPROPERTY(EditAnywhere, Category="Interactable Properties")
	int32 InteractableAmount=1;

};
