// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_WaitTime.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/FPS_Zombie.h"
#include "Zombie/AI/FPS_ZombieTargetPoint.h"

EBTNodeResult::Type UFPS_WaitTime::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), FMath::RandRange(MinWait, MaxWait));

	return EBTNodeResult::Succeeded;
}
