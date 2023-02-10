// Fill out your copyright notice in the Description page of Project Settings.


#include "WZ_GuardCharacter.h"

#include "AI_WZ_PatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Internal/Kismet/BlueprintTypeConversions.h"

// Sets default values
AWZ_GuardCharacter::AWZ_GuardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWZ_GuardCharacter::BeginPlay()
{
	Super::BeginPlay();

	TorchComp = FindComponentByClass<UStaticMeshComponent>();
	PatrolController=Cast<AAI_WZ_PatrolController>(GetController());
	UpdateAlertState(AlertSTATE::Peaceful);
}

void AWZ_GuardCharacter::UpdateAlertState(int32 NewState)
{
	switch(NewState)
	{
	case 0:{
			CurrentTorchColor=PeacefulColor;
			break;
	}
	case 1:{
			CurrentTorchColor=SuspiciousColor;
			break;
	}
	case 2:{
			CurrentTorchColor=AlertedColor;
			break;
	}
	}
	FVector CurrentColorVector=FVector(CurrentTorchColor.R,CurrentTorchColor.G,CurrentTorchColor.B);
	TorchComp->SetVectorParameterValueOnMaterials("Color Emission",CurrentColorVector);
}

// Called every frame
void AWZ_GuardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int32 AlertState=PatrolController->GetBlackboardComponent()->GetValueAsEnum("AlertState");
	UpdateAlertState(AlertState);

}

// Called to bind functionality to input
void AWZ_GuardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

