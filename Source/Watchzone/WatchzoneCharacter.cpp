// Copyright Epic Games, Inc. All Rights Reserved.

#include "WatchzoneCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Interactor/Interactable.h"
#include "Interactor/InventoryItem.h"
#include "Containers/Map.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AWatchzoneCharacter

AWatchzoneCharacter::AWatchzoneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));
	InventoryComp = CreateDefaultSubobject<UWZ_AC_Inventory>(TEXT("InventoryComp"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AWatchzoneCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	bIsCrouched=false;
}

void AWatchzoneCharacter::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	if (SoundToPlay)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation(), Volume);
		MakeNoise(Volume, this, GetActorLocation());
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWatchzoneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Crouching);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Look);
		
		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Interact);

		//Throwing
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Throw);

		//Dropping
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Drop);

		//Scrolling in inventory
		EnhancedInputComponent->BindAction(ScrollInventoryAction, ETriggerEvent::Triggered, this, &AWatchzoneCharacter::Scrolling);

	}

}

void AWatchzoneCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWatchzoneCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWatchzoneCharacter::Crouching(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString("Crouch Triggered"));
	bIsCrouching=!bIsCrouching;
}

void AWatchzoneCharacter::Interact(const FInputActionValue& Value)
{
	TArray<AActor*> OverlappingActors;
	TSubclassOf<AInteractable> InteractableClass;
	GetOverlappingActors(OverlappingActors,InteractableClass);
	if (!OverlappingActors.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"Overlapping actors not empty");
		AInteractable* InteractableItem = Cast<AInteractable>(OverlappingActors[0]);
		
		bool IsSuccess = InventoryComp->AddItemOnInventory(InteractableItem);
		if (IsSuccess)
		{
			InteractableItem->Interact();
		}
	}
}

void AWatchzoneCharacter::Throw(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Black,TEXT("Throwing triggered"));
	if(InventoryComp->GetPlayerInventory()[InventoryComp->GetCurrentActiveInventorySlot()]->GetInventoryId()==0)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Black,TEXT("Throwing is possible on this slot"));
		bIsThrowing=true;
		InventoryComp->ThrowInteractableFromInventory(InventoryComp->GetCurrentActiveInventorySlot());
	}
	bIsThrowing=false;
}

void AWatchzoneCharacter::Drop(const FInputActionValue& Value)
{
	if(InventoryComp->GetPlayerInventory()[InventoryComp->GetCurrentActiveInventorySlot()]->GetInventoryId()!=-1)
		InventoryComp->DropInteractableFromInventory(InventoryComp->GetCurrentActiveInventorySlot(),1);
}

void AWatchzoneCharacter::Scrolling(const FInputActionValue& Value)
{
	float ScrollAxis = Value.Get<float>();

	InventoryComp->SwitchCurrentActiveSlot(false);
	if(ScrollAxis<0)
	{
		InventoryComp->SetCurrentActiveInventorySlot(InventoryComp->GetCurrentActiveInventorySlot()-1);
		if(InventoryComp->GetCurrentActiveInventorySlot()<0)
		{
			InventoryComp->SetCurrentActiveInventorySlot(InventoryComp->GetInventoryCapacity()-1);
		}
	}
	else if (ScrollAxis>0)
	{
		InventoryComp->SetCurrentActiveInventorySlot(InventoryComp->GetCurrentActiveInventorySlot()+1);
		if(InventoryComp->GetCurrentActiveInventorySlot()>InventoryComp->GetInventoryCapacity()-1)
		{
			InventoryComp->SetCurrentActiveInventorySlot(0);
		}
	}
	InventoryComp->SwitchCurrentActiveSlot(true);
}

void AWatchzoneCharacter::SetIsThrowing(bool NewThrowingValue)
{
	bIsThrowing=NewThrowingValue;
}

bool AWatchzoneCharacter::GetIsThrowing()
{
	return bIsThrowing;
}









