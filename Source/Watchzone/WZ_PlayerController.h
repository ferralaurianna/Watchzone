// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WZ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WATCHZONE_API AWZ_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWZ_PlayerController();

	bool ApplyHUD();

	UUserWidget* GetGameWidget();

protected:
	UPROPERTY(EditAnywhere,Category="HUD Widgets")
	class TSubclassOf<UUserWidget> GameHUDClass;

	UUserWidget* GameWidget;

	virtual void BeginPlay() override;
};
