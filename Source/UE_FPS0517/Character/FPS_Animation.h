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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "info")
		float AimYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "info")
		float AimPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsIronsight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsSprint = false;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsProne = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsProning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsFire = false;

	UFUNCTION()
		void AnimNotify_ProneStart(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_ProneEnd(UAnimNotify* Notify);
};
