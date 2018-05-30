// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Controller.h"
#include "Camera/FPS_CameraMng.h"

AFPS_Controller::AFPS_Controller()
{
	PlayerCameraManagerClass = AFPS_CameraMng::StaticClass();
}
