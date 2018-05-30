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
		Pawn->GetCharacterMovement()->MaxWalkSpeed = Pawn->walkSpeed;
	}
}

void UAnimNotifyState_ZombieMove::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AFPS_Zombie* Pawn = Cast<AFPS_Zombie>(MeshComp->GetOwner());
	if (Pawn)
	{
		Pawn->GetCharacterMovement()->MaxWalkSpeed = 20.0f;
	}
}
