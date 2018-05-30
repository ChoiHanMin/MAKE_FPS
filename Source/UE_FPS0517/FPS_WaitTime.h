// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FPS_WaitTime.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UFPS_WaitTime : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		float MinWait = 0.0f;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		float MaxWait = 0.0f;
};
