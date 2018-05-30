// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CheckChase.h"
#include "Zombie/FPS_Zombie.h"
#include "Character/FPS_Character.h"
#include "Zombie/AI/FPS_ZombieAIControll.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_CheckChase::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AFPS_Zombie* Zombie = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());

	AFPS_Character* Player = Cast<AFPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	float Range = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
	FVector Dir = Player->GetActorLocation() - Zombie->GetActorLocation();


	if (Range <= Zombie->AttackRange)
	{
		Zombie->CurrentState = EZombieState::BATTLE;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);

		return EBTNodeResult::Failed;
	}
	else if (Range > Zombie->PawnSensing->SightRadius)
	{
		Zombie->CurrentState = EZombieState::NORMAL;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
		return EBTNodeResult::Failed;
	}
	else
	{
		FVector TraceStart = Zombie->GetActorLocation();
		FVector TraceEnd = Player->GetActorLocation();

		FHitResult OutHit;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TArray<AActor*> IgnoreObjects;

		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		IgnoreObjects.Add(Zombie);

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectTypes, false, IgnoreObjects, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Blue, FLinearColor::Red, 5.0f);

		if (Result)
		{
			if (!(OutHit.GetActor()->ActorHasTag(FName(TEXT("Player")))))
			{
				Zombie->CurrentState = EZombieState::NORMAL;
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
				return EBTNodeResult::Failed;
			}
		}
	}
	return EBTNodeResult::Succeeded;
}
