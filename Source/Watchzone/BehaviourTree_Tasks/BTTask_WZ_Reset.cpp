// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WZ_Reset.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_WZ_Reset::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BlackboardKey.SelectedKeyName,0);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

