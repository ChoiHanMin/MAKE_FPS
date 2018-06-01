// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_ZombiePatrol.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/FPS_Zombie.h"
#include "Zombie/AI/FPS_ZombieTargetPoint.h"


EBTNodeResult::Type UFPS_ZombiePatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		AFPS_ZombieTargetPoint* Point = Pawn->PatrolPoints[FMath::RandRange(0, Pawn->PatrolPoints.Num() - 1)];

		// 블랙보드 등록.
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Point);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
