// Fill out your copyright notice in the Description page of Project Settings.


#include "WZ_AC_Inventory.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Items/InteractItems/DistractingNoisingItem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Watchzone/WZ_PlayerController.h"

class UWidget;
class UWidgetTree;
// Sets default values for this component's properties
UWZ_AC_Inventory::UWZ_AC_Inventory()
{

}


// Called when the game starts
void UWZ_AC_Inventory::BeginPlay()
{
	Super::BeginPlay();
	PlayerInventory.SetNum(InventoryCapacity);
	for (int i=0;i<InventoryCapacity;i++)
	{
		PlayerInventory[i]=Cast<UInventoryItem>(NewObject<UWZ_EmptyInventoryItem>(this,EmptyItemClass));
	}

	for (const TPair<int32, TSubclassOf<UInventoryItem>>& pair : ItemMapClass)
	{
		if(pair.Value!=nullptr)
		{
			UInventoryItem* Item = NewObject<UInventoryItem>(this,pair.Value);
			ItemMap.Add(pair.Key,Item);
		}
	}

	SwitchCurrentActiveSlot(true);
	
}

bool UWZ_AC_Inventory::AddItemOnInventory(AInteractable* InteractableItem)
{
	bool WasAdded=false;

	int count=0;
	for(count=0;count<InventoryCapacity;count++)
	{
		if(PlayerInventory[count]!=nullptr && PlayerInventory[count]->GetInventoryId()==InteractableItem->GetInteractableId())
		{
			PlayerInventory[count]->UpdateStorageSize(InteractableItem->GetAmount());
			WasAdded=true;
			break;
		}
	}
	
	if(!WasAdded)
	{
		for(int i=0;i<InventoryCapacity;i++)
		{
			if(PlayerInventory[i]->GetInventoryId()==-1)
			{
				GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Interactable : "+FString::FromInt(InteractableItem->GetInteractableId())));
				UInventoryItem** Item= ItemMap.Find(InteractableItem->GetInteractableId());
				if(*Item!=nullptr)
				{
					PlayerInventory[i] = *Item;
					PlayerInventory[i]->UpdateStorageSize(InteractableItem->GetAmount());
					GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Item : "+FString::FromInt(PlayerInventory[i]->GetInventoryId())));
					WasAdded=true;
				}
				break;
			}
		}
	}
	return WasAdded;
}

bool UWZ_AC_Inventory::DropInteractableFromInventory(int32 SlotInInventory, int32 AmountBeingDropped)
{
	bool WasDrop = false;
	
	if (SlotInInventory>=0 && SlotInInventory<InventoryCapacity)
	{
		UInventoryItem* Item = PlayerInventory[SlotInInventory];
		TSubclassOf<AInteractable>* InteractableClass = InteractableMap.Find(Item->GetInventoryId());

		FVector OffsetPosition(100.f,0.f,0.f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FVector Location = GetOwner()->GetActorLocation()+OffsetPosition;
		AInteractable* Interactable = GetWorld()->SpawnActor<AInteractable>(*InteractableClass,Location, Rotation);

		if(Interactable!=nullptr)
		{
			PlayerInventory[SlotInInventory]->UpdateStorageSize(-AmountBeingDropped);
			if (PlayerInventory[SlotInInventory]->GetStorageSize()<=0)
			{
				PlayerInventory[SlotInInventory]=Cast<UInventoryItem>(NewObject<UWZ_EmptyInventoryItem>(this,EmptyItemClass));;
			}
			WasDrop = true;
		}
	}
	
	return WasDrop;
}

bool UWZ_AC_Inventory::ThrowInteractableFromInventory(int32 SlotInInventory)
{
	bool HasBeenThrowned = false;

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Throwing is called"));
	if (SlotInInventory>=0 && SlotInInventory<InventoryCapacity)
	{
		UInventoryItem* Item = PlayerInventory[SlotInInventory];
		TSubclassOf<AInteractable>* InteractableClass = InteractableMap.Find(Item->GetInventoryId());

		FVector OffsetPosition(60.f,0.f,0.f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FVector Location = GetOwner()->GetActorLocation()+OffsetPosition;
		AInteractable* Interactable = GetWorld()->SpawnActor<AInteractable>(*InteractableClass,Location, Rotation);
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Interactable->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (StaticMesh!=nullptr)
		{
			ADistractingNoisingItem* InteractableThrown = Cast<ADistractingNoisingItem>(Interactable);
			StaticMesh->SetPhysicsLinearVelocity(UKismetMathLibrary::GetDirectionUnitVector(GetOwner()->GetActorLocation(),Location)*InteractableThrown->GetSpeed());
		}

		if(Interactable!=nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Dropping is a success"));
			PlayerInventory[SlotInInventory]->UpdateStorageSize(-1);
			if (PlayerInventory[SlotInInventory]->GetStorageSize()<=0)
			{
				PlayerInventory[SlotInInventory]=Cast<UInventoryItem>(NewObject<UWZ_EmptyInventoryItem>(this,EmptyItemClass));;
			}
			HasBeenThrowned = true;
		}
	}
	
	return HasBeenThrowned;
}

void UWZ_AC_Inventory::SwitchCurrentActiveSlot(bool bIsForTheNewSlot)
{
	AWZ_PlayerController* PlayerController = Cast<AWZ_PlayerController>(UGameplayStatics::GetPlayerController(GetOwner(), 0));
	UWidgetTree* UserWidgetTree = PlayerController->GetGameWidget()->WidgetTree;
	UUserWidget* InventoryWidget = Cast<UUserWidget>(UserWidgetTree->FindWidget(FName("WBP_Inventory")));

	UWidgetTree* InventoryWidgetTree = InventoryWidget->WidgetTree;
	UWidget* BackgroundImageSlotWidget = InventoryWidgetTree->FindWidget(FName("Background_"+FString::FromInt(CurrentActiveInventorySlot)));
	if(BackgroundImageSlotWidget!=nullptr)
	{
		if (bIsForTheNewSlot)
			BackgroundImageSlotWidget->SetRenderOpacity(2);
		else
			BackgroundImageSlotWidget->SetRenderOpacity(0.7);
	}
}

TArray<UInventoryItem*> UWZ_AC_Inventory::GetPlayerInventory()
{
	return PlayerInventory;
}

int32 UWZ_AC_Inventory::GetInventoryCapacity()
{
	return InventoryCapacity;
}

int32 UWZ_AC_Inventory::GetCurrentActiveInventorySlot()
{
	return CurrentActiveInventorySlot;
}

void UWZ_AC_Inventory::SetCurrentActiveInventorySlot(int32 NewSlot)
{
	CurrentActiveInventorySlot=NewSlot;
}

