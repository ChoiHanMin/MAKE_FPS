// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_StateCheck.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UBTService_StateCheck : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
