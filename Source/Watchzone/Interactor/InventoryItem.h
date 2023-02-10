// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class WATCHZONE_API UInventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	UInventoryItem();

	void UpdateStorageSize(int32 AmountToAddOrRetrieve);

	int32 GetInventoryId();
	int32 GetStorageCapacity();
	int32 GetStorageSize();

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 ItemId;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 StorageSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 StorageCapacity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemThumbnail;
};
