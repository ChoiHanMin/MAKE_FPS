// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_CameraShake.h"



UFPS_CameraShake::UFPS_CameraShake()
{
	OscillationDuration = 0.1f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = 15.0f;
	RotOscillation.Pitch.Frequency = 1.0f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;

}
