// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_SetZombieState.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/FPS_Zombie.h"
#include "Zombie/AI/FPS_ZombieTargetPoint.h"

EBTNodeResult::Type UFPS_SetZombieState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());

	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->CurrentState = newZombieState;
		Pawn->CurrentAnimState = newZombieAnimState;
		//UE_LOG(LogClass, Warning, TEXT("상태변경! "));

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)newZombieState);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
