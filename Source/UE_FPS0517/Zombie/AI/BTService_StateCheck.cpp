// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_StateCheck.h"
#include "Zombie/FPS_Zombie.h"
#include "Zombie/AI/FPS_ZombieAIControll.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"


void UBTService_StateCheck::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPS_Zombie* Zombie = Cast<AFPS_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	float Range = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
/*
	FVector TraceStart = Zombie->GetActorLocation();
	FVector TraceEnd = Zombie->GetActorLocation() * 8000.0f;
	FHitResult OutHit;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreObjects;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	IgnoreObjects.Add(Zombie);

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectTypes, false, IgnoreObjects, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Blue, FLinearColor::Red, 5.0f);
*/
	if (Zombie)
	{
		switch (Zombie->CurrentState)
		{
		case EZombieState::BATTLE:
			// 때렸는데 쫒아올 때
			if (Zombie->Hit)
			{
			/*	if (Range >= Zombie->AttackRange)
				{
					Zombie->CurrentState = EZombieState::CHASE;
					OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
				
				}
				else
				{
					Zombie->CurrentState = EZombieState::BATTLE;
					OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
				}*/
			}
			break;

		case EZombieState::CHASE:

			if (Range >= Zombie->AttackRange)
			{
				Zombie->CurrentState = EZombieState::BATTLE;
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);

			}
			else if (Range > Zombie->PawnSensing->SightRadius)
			{
				Zombie->CurrentState = EZombieState::NORMAL;
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
			}
			// 시야가 막혀있으면 돌아감., - 라인트레이싱.

			/*if (Result)
			{
				Zombie->CurrentState = EZombieState::NORMAL;
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Zombie->CurrentState);
			}*/
			break;
		}
	}
}
