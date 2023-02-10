// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
}

void UInventoryItem::UpdateStorageSize(int32 AmountToAdd)
{
	StorageSize=StorageSize+AmountToAdd;
	if (StorageSize<0)
		StorageSize=0;
	else if (StorageSize>=StorageCapacity)
		StorageSize=StorageCapacity;
}

int32 UInventoryItem::GetInventoryId()
{
	return ItemId;
}

int32 UInventoryItem::GetStorageCapacity()
{
	return StorageCapacity;
}

int32 UInventoryItem::GetStorageSize()
{
	return StorageSize;
}
