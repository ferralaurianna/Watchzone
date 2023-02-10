// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Interactor/WZ_AC_Inventory.h"
#include "WatchzoneCharacter.generated.h"


UCLASS(config=Game)
class AWatchzoneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Throw Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrowAction;

	/** Drop Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DropAction;

	/** Scrolling in Inventory Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ScrollInventoryAction;
	

public:
	AWatchzoneCharacter();

	bool GetIsThrowing();
	void SetIsThrowing(bool NewThrowingValue);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for crouching input */
	void Crouching(const FInputActionValue& Value);

	/** Called for interacting input */
	void Interact(const FInputActionValue& Value);

	/** Called for throwing input */
	void Throw(const FInputActionValue& Value);

	/** Called for dropping input */
	void Drop(const FInputActionValue& Value);

	/** Called for scrolling in inventory input */
	void Scrolling(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = AI)
	void ReportNoise(USoundBase* SoundToPlay,float Volume);
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UWZ_AC_Inventory* InventoryComp;

	UPROPERTY(BlueprintReadWrite,Category= "Character")
	bool bIsThrowing=false;

	UPROPERTY(BlueprintReadWrite,Category= "Character")
	bool bIsCrouching=false;
	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

