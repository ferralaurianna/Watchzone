// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_WZ_PatrolController.h"

#include "WZ_GuardCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAI_WZ_PatrolController::AAI_WZ_PatrolController()
{
	
}

void AAI_WZ_PatrolController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GLog->Log("!! AIController has possessed the character !!");
	
	bool bTreeIsRunning = RunBehaviorTree(BehaviorTreePatrol);
	if(!bTreeIsRunning)
		GLog->Log("!! Tree Running results : false !!");
	if (bTreeIsRunning)
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,FString("Tree is running"));
};
