// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_ZombieAnim.h"
#include "Zombie/FPS_Zombie.h"

void UFPS_ZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(TryGetPawnOwner());

	if (Pawn&&Pawn->IsValidLowLevel())
	{
		CurrentState = Pawn->CurrentState;
		CurrentAnimState = Pawn->CurrentAnimState;
	}
}

void UFPS_ZombieAnim::AnimNotify_StartAttack(UAnimNotify * Notify)
{
	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(TryGetPawnOwner());
	if (Pawn&&Pawn->IsValidLowLevel())
	{
	Pawn->OnAttack();
	}
}
