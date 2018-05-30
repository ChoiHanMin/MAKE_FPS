// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_ZombieAIControll.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Zombie/FPS_Zombie.h"

AFPS_ZombieAIControll::AFPS_ZombieAIControll()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBaord"));
}

void AFPS_ZombieAIControll::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AFPS_Zombie* Zombie = Cast<AFPS_Zombie>(InPawn);

	if (Zombie)
	{
		BBComponent->InitializeBlackboard(*(Zombie->Behaviortree->BlackboardAsset));
		BTComponent->StartTree(*(Zombie->Behaviortree));
		//UE_LOG(LogClass, Warning, TEXT("black"));
	}

}
