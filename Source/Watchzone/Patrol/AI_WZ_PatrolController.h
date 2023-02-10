// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Watchzone/Patrol/A_WZ_PatrolPoint.h"
#include "AI_WZ_PatrolController.generated.h"

/**
 * 
 */
UCLASS()
class WATCHZONE_API AAI_WZ_PatrolController : public AAIController
{
	GENERATED_BODY()
public:
	AAI_WZ_PatrolController();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBehaviorTree* BehaviorTreePatrol;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	class UBlackboardComponent* BlackboardPatrol;
	class UBehaviorTreeComponent* BehaviorTreePatrolComp;
};
