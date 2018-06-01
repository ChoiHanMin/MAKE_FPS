// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_Controller.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API AFPS_Controller : public APlayerController
{
	GENERATED_BODY()
public:
	AFPS_Controller();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	class UItemTooltipWidget* ItemTooltip;
	
	
};
