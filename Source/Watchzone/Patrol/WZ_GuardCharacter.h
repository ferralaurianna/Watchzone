// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_WZ_PatrolComponent.h"
#include "GameFramework/Character.h"
#include "WZ_GuardCharacter.generated.h"

UCLASS()
class WATCHZONE_API AWZ_GuardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWZ_GuardCharacter();

	void UpdateAlertState(int32 NewState);

	enum AlertSTATE
    {
    	Peaceful,
    	Suspicious,
    	Alerted
    };
    
	UPROPERTY(BlueprintReadWrite)
	int32 GuardAlert=AlertSTATE::Peaceful;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	class UAC_WZ_PatrolComponent* PatrolComp;
	class UStaticMeshComponent* TorchComp;

	FLinearColor CurrentTorchColor;
	class AAI_WZ_PatrolController* PatrolController;

	UPROPERTY(EditAnywhere)
	FLinearColor PeacefulColor;
	UPROPERTY(EditAnywhere)
	FLinearColor SuspiciousColor;
	UPROPERTY(EditAnywhere)
	FLinearColor AlertedColor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
