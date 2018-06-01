// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemTooltipWidget.h"
#include "Components/TextBlock.h"

void UItemTooltipWidget::NativeConstruct()
{
	ItemName = Cast <UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}


