// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackOn.h"
#include "Zombie/FPS_Zombie.h"
#include "Character/FPS_Character.h"
#include "Zombie/AI/FPS_ZombieAIControll.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UBTTask_AttackOn::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AFPS_Zombie* Zombie = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());

	AFPS_Character* Player = Cast<AFPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	float Range = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
	FVector Dir = Player->GetActorLocation() - Zombie->GetActorLocation();

	// 공격할 때 플레이어 방향쪽으로 좀비를 틀어준다.
	Zombie->SetActorRotation(Dir.Rotation());

	if (Range >= Zombie->AttackRange)
	{
		Zombie->CurrentState = EZombieState::CHASE;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);

		return EBTNodeResult::Failed;
	}
	else if (Player->CurrentHP <= 0)
	{
		Zombie->CurrentState = EZombieState::NORMAL;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
		
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}