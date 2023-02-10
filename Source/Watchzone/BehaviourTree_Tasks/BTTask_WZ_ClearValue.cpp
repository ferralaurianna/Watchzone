// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WZ_ClearValue.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_WZ_ClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(BlackboardComp)
	{
		BlackboardComp->ClearValue(BlackboardKey.SelectedKeyName);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
