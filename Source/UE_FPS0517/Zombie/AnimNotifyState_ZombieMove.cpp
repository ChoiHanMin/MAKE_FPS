// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_ZombieMove.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Zombie/FPS_Zombie.h"

void UAnimNotifyState_ZombieMove::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(MeshComp->GetOwner());
	if (Pawn)
	{

	}
}

void UAnimNotifyState_ZombieMove::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(MeshComp->GetOwner());
	if (Pawn)
	{
		// FSM에서도 걷기중에 상태가 바뀌어도 애님노티파이가 실행돼서 추적 상태에서도 속도가 3이됨.
		if (Pawn->CurrentState == EZombieState::NORMAL)
		{
			Pawn->GetCharacterMovement()->MaxWalkSpeed = Pawn->walkSpeed;
		}
	}
}

void UAnimNotifyState_ZombieMove::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(MeshComp->GetOwner());
	if (Pawn)
	{
		if (Pawn->CurrentState == EZombieState::NORMAL)
		{
			Pawn->GetCharacterMovement()->MaxWalkSpeed = 2.0f;
		}
	}
}
