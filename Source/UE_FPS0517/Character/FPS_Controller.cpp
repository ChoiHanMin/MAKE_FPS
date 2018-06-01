// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Controller.h"
#include "Camera/FPS_CameraMng.h"
#include "ConstructorHelpers.h"
#include "ItemTooltipWidget.h"


AFPS_Controller::AFPS_Controller()
{
	PlayerCameraManagerClass = AFPS_CameraMng::StaticClass();
}

void AFPS_Controller::BeginPlay()
{
	FStringClassReference ItemTooltipWidjet(TEXT("WidgetBlueprint'/Game/BluePrints/Item/WG_Item.WG_Item'"));
	if (UClass* myWidgetclass = ItemTooltipWidjet.TryLoadClass<UUserWidget>())
	{
		ItemTooltip = Cast<UItemTooltipWidget>(CreateWidget<UUserWidget>(this, myWidgetclass));
		ItemTooltip->AddtoViewPort();

		ItemTooltip->SetVisibility(ESlatevisibility::Collapsed);
	}
}
