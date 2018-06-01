// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "ItemTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS0517_API UItemTooltipWidget : public UWidgetBlueprint
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UTextBlock* ItemName;
};
