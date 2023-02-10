// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_WZ_Patrol.h"

#include <string>

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Watchzone/Patrol/AC_WZ_PatrolComponent.h"
#include "Watchzone/Patrol/AI_WZ_PatrolController.h"
#include "Watchzone/Patrol/A_WZ_PatrolPoint.h"

inline EBTNodeResult::Type UBTTaskNode_WZ_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString("HERE"));
	AAI_WZ_PatrolController* AIController = Cast<AAI_WZ_PatrolController>(OwnerComp.GetAIOwner());
	UAC_WZ_PatrolComponent* PatrolComp = Cast<UAC_WZ_PatrolComponent>(AIController->GetCharacter()->GetComponentByClass(UAC_WZ_PatrolComponent::StaticClass()));

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComp && PatrolComp)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString("HEREEEEEEEEEEEE"));

		TArray<AA_WZ_PatrolPoint*> AvailablePatrolPoints = PatrolComp->GetPatrolPoints();
		
		AA_WZ_PatrolPoint* NextPatrolPoint = nullptr;

		if (PatrolComp->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AA_WZ_PatrolPoint>(AvailablePatrolPoints[++PatrolComp->CurrentPatrolPoint]);
		}
		else
		{
			NextPatrolPoint = Cast<AA_WZ_PatrolPoint>(AvailablePatrolPoints[0]);
			PatrolComp->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}