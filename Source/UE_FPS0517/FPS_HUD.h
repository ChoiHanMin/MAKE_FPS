// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API AFPS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AFPS_HUD();

	virtual void DrawHUD() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* CrossHair;
};
