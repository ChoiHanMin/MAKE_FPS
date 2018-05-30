// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS_ZombieHPBarWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UFPS_ZombieHPBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float Percent=0.0f;
	
	
	
};
