// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTaskNode.h"
#include "Zombie/FPS_Zombie.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTaskNode::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Pawn && Pawn->IsValidLowLevel())
	{

		switch (Pawn->CurrentAnimState)
		{
		case EZombieAnimState::RUN:
			Pawn->GetCharacterMovement()->MaxWalkSpeed = Pawn->runSpeed;
			break;
		case EZombieAnimState::WALK:
			Pawn->GetCharacterMovement()->MaxWalkSpeed = Pawn->walkSpeed;
			break;
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
