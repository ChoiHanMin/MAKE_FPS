// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPS_ZombieAIControll.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API AFPS_ZombieAIControll : public AAIController
{
	GENERATED_BODY()
public:

	AFPS_ZombieAIControll();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* BBComponent;

	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;	
};
