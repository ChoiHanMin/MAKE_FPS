// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_HUD.h"
#include "ConstructorHelpers.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"

AFPS_HUD::AFPS_HUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> T_CrossHair(TEXT("Texture2D'/Game/Weapons/crosshair.crosshair'"));
	if (T_CrossHair.Succeeded())
	{
		CrossHair = T_CrossHair.Object;
	}
}

void AFPS_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrossHair)
	{
		DrawTextureSimple(CrossHair, Canvas->SizeX / 2 - CrossHair->GetSizeX() / 2, Canvas->SizeY / 2 - CrossHair->GetSizeY() / 2);
	}
}
