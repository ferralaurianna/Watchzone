// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "Items/InventoryItems/WZ_EmptyInventoryItem.h"
#include "Interactable.h"
#include "WZ_AC_Inventory.generated.h"


UCLASS( Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WATCHZONE_API UWZ_AC_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWZ_AC_Inventory();

	bool AddItemOnInventory(AInteractable* Interactable);
	bool DropInteractableFromInventory(int32 SlotInInventory,int32 AmountBeingDropped);
	bool ThrowInteractableFromInventory(int32 SlotInInventory);
	
	void SwitchCurrentActiveSlot(bool bIsForTheNewSlot);

	TArray<UInventoryItem*> GetPlayerInventory();
	int32 GetInventoryCapacity();
	int32 GetCurrentActiveInventorySlot();

	void SetCurrentActiveInventorySlot(int32 NewSlot);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,Category="Inventory")
	TArray<UInventoryItem*> PlayerInventory;

	UPROPERTY(EditAnywhere, Category= "Inventory Properties")
	int32 InventoryCapacity=4;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 CurrentActiveInventorySlot=0;

	UPROPERTY(EditAnywhere, Category="Inventory Propreties")
	TSubclassOf<UWZ_EmptyInventoryItem> EmptyItemClass;

	UPROPERTY(EditDefaultsOnly, Category= "Inventory Properties")
	TMap<int32,TSubclassOf<UInventoryItem>> ItemMapClass;

	UPROPERTY(BlueprintReadOnly)
	TMap<int32,UInventoryItem*> ItemMap;

	UPROPERTY(EditDefaultsOnly, Category= "Inventory Properties")
	TMap<int32,TSubclassOf<AInteractable>> InteractableMap;

		
};
