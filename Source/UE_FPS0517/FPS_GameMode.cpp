// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_GameMode.h"
#include "FPS_Controller.h"
#include "Character/FPS_Character.h"
#include "FPS_HUD.h"
#include "ConstructorHelpers.h"


AFPS_GameMode::AFPS_GameMode()
{
	static ConstructorHelpers::FClassFinder<AFPS_Controller> PC_Class(TEXT("Blueprint'/Game/BluePrints/BP_FPS_Controller.BP_FPS_Controller_C'"));
	if (PC_Class.Succeeded())
	{
		//PlayerControllerClass = AFPS_Controller::StaticClass();
		PlayerControllerClass = PC_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<AFPS_Character> Pawn_Class(TEXT("Blueprint'/Game/BluePrints/BP_FPS_Character.BP_FPS_Character_C'"));
	if (Pawn_Class.Succeeded())
	{		
		//DefaultPawnClass = AFPS_Character::StaticClass();
		DefaultPawnClass = Pawn_Class.Class;
	}
	HUDClass = AFPS_HUD::StaticClass();
	
}
