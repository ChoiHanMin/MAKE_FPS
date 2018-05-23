// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Animation.h"
#include "Character/FPS_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPS_Animation::NativeUpdateAnimation(float DeltaSeconds)
{
	// 무조건 상속받은 함수는 슈퍼를 써서 호출을 해줘야함.
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	AFPS_Character* Pawn = Cast<AFPS_Character>(TryGetPawnOwner());

	if (Pawn && Pawn->IsValidLowLevel())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());

		bIsCrouch = Pawn->bIsCrouched;

		AimYaw = Pawn->GetAimOffset().Yaw;
		AimPitch = Pawn->GetAimOffset().Pitch;
		bIsIronsight = Pawn->bIsIronsight;
		bIsSprint = Pawn->bIsSprint;
		bIsProning = Pawn->bIsProne;
	}

}

void UFPS_Animation::AnimNotify_ProneStart(UAnimNotify* Notify)
{
	AFPS_Character* Pawn = Cast<AFPS_Character>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->bIsProning = true;
	}
}

void UFPS_Animation::AnimNotify_ProneEnd(UAnimNotify* Notify)
{
	AFPS_Character* Pawn = Cast<AFPS_Character>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->bIsProning = false;
	}
}
