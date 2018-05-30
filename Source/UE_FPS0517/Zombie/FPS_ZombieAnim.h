// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Zombie/FPS_Zombie.h"
#include "FPS_ZombieAnim.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UFPS_ZombieAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		EZombieState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		EZombieAnimState CurrentAnimState;

	UFUNCTION()
	void AnimNotify_StartAttack(UAnimNotify* Notify);
	
};
