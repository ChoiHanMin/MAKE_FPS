// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_CameraMng.h"
#include "Character/FPS_Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AFPS_CameraMng::AFPS_CameraMng()
{

}

void AFPS_CameraMng::BeginPlay()
{
	Super::BeginPlay();
}

void AFPS_CameraMng::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	FVector TargetOffset;

	AFPS_Character* Pawn = PCOwner ? Pawn = Cast<AFPS_Character>(PCOwner->GetPawn()) : nullptr;

	if (Pawn)
	{
		 // 조준 모션에 따른 FOV조절.

		float TargetFOV = Pawn->bIsIronsight ? IronSightFOV : NormalFOV;
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 5.0f);
		SetFOV(DefaultFOV);

		 // 자세에 따른 카메라 위치 보간.
		if (Pawn->bIsCrouched)
		{
			TargetOffset = Pawn->CrouchSpringArmPosition; // -32
		}
		else if (Pawn->bIsProne)
		{
			TargetOffset = Pawn->ProneSpringArmPosition; // -80
		}
		else
		{
			TargetOffset = Pawn->NormalSpringArmPosition; // -0
		}

		//CrouchOffset = Pawn->bIsCrouched ? Pawn->CrouchedEyeHeight : 0;

		SpringArmOffset = FMath::VInterpTo(SpringArmOffset, TargetOffset, DeltaTime, 5.0f);

		 // 카메라 가져오기
		//FVector CurrentSpringarm = Pawn->SpringArm->GetRelativeTransform().GetLocation();

		//// 카메라 위치 구하기
		//FVector NewCameraLocation = FVector(CurrentCameraLocation.X, CurrentCameraLocation.Y, DefaultCameraZ - CrouchOffset);


		//UE_LOG(LogClass, Warning, TEXT("%s"), *CurrentSpringarm.ToString());

		//// 캐릭터에 넣어주기
		Pawn->SpringArm->SetRelativeLocation(SpringArmOffset);
	}

}
