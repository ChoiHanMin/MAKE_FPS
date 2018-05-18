// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPS_Animation.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UFPS_Animation : public UAnimInstance
{
	GENERATED_BODY()

public:
	

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "info")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "info")
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "info")
		bool bIsCrouch;
};
