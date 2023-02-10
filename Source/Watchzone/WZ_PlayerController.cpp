// Fill out your copyright notice in the Description page of Project Settings.


#include "WZ_PlayerController.h"

#include "Blueprint/UserWidget.h"

AWZ_PlayerController::AWZ_PlayerController()
{
	
}

bool AWZ_PlayerController::ApplyHUD()
{
	this->bShowMouseCursor = false;
	this->bEnableClickEvents = false;
	GameWidget = CreateWidget<UUserWidget>(GetWorld(),GameHUDClass);
	if(GameWidget != NULL)
	{
		GameWidget->bIsFocusable=false;
		GameWidget->AddToViewport();
		return true;
	}
	return false;
}

UUserWidget* AWZ_PlayerController::GetGameWidget()
{
	return GameWidget;
}

void AWZ_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	ApplyHUD();
}

