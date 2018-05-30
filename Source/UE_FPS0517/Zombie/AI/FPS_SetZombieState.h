// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Zombie/FPS_Zombie.h"
#include "FPS_SetZombieState.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UFPS_SetZombieState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		EZombieState newZombieState;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		EZombieAnimState newZombieAnimState;
	
	
};
