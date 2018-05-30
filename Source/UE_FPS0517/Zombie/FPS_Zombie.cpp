// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Zombie.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "Character/FPS_Character.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "Zombie/AI/FPS_ZombieAIControll.h"
#include "Zombie/AI/FPS_ZombieTargetPoint.h"

// Sets default values
AFPS_Zombie::AFPS_Zombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Zombie(TEXT("SkeletalMesh'/Game/Zombie/Mesh/Zombie.Zombie'"));
	if (SK_Zombie.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Zombie.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	FStringClassReference Anim_Zombie_Ref(TEXT("AnimBlueprint'/Game/BluePrints/Animations/ABP_Zombie.ABP_Zombie_C''"));
	if (UClass* Anim_Male_Class = Anim_Zombie_Ref.TryLoadClass<UAnimInstance>())
	{
		GetMesh()->SetAnimInstanceClass(Anim_Male_Class);
	}

	CurrentState = EZombieState::NORMAL;
	CurrentAnimState = EZombieAnimState::IDLE;


	AIControllerClass = AFPS_ZombieAIControll::StaticClass();

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Zombie(TEXT("BehaviorTree'/Game/Zombie/AI/BT_Zombie.BT_Zombie'"));
	if (BT_Zombie.Succeeded())
	{
		Behaviortree = BT_Zombie.Object;
	}

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 300.0f;
	PawnSensing->SetPeripheralVisionAngle(30.0f);

}

// Called when the game starts or when spawned
void AFPS_Zombie::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	TArray<AActor*> Outer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPS_ZombieTargetPoint::StaticClass(), Outer);

	for (int i = 0; i < Outer.Num(); i++)
	{
		PatrolPoints.Add(Cast<AFPS_ZombieTargetPoint>(Outer[i]));
	}

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AFPS_Zombie::OnSeePawn);
		PawnSensing->OnHearNoise.AddDynamic(this, &AFPS_Zombie::OnHearNoise);
	}
}

void AFPS_Zombie::OnSeePawn(APawn* Pawn)
{
	AFPS_Character* Player = Cast<AFPS_Character>(Pawn);
	if (Player)
	{
		AFPS_ZombieAIControll* AIC = Cast<AFPS_ZombieAIControll>(GetController());
		if (AIC)
		{
			CurrentState = EZombieState::CHASE;
			CurrentAnimState = EZombieAnimState::RUN;

			AIC->BBComponent->SetValueAsObject(FName(TEXT("Target")),Player);
			AIC->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);		
		}
	}
}

void AFPS_Zombie::OnHearNoise(APawn* Pawn, const FVector& Location, float Volme)
{

}

// Called every frame
void AFPS_Zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPS_Zombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AFPS_Zombie::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP <= 0)
	{
		return 0;
	}

	Hit = true;
	if (Hit)
	{
		UE_LOG(LogClass, Warning, TEXT("좀비 읔읔읔읔"));
	}

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

	

		if (PointDamageEvent->HitInfo.BoneName.Compare(FName(TEXT("head"))) == 0)
		{
			UE_LOG(LogClass, Warning, TEXT("좀비 머리 읔 %s"), *PointDamageEvent->HitInfo.BoneName.ToString());
			CurrentHP = 0;
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("좀비 읔 %s"), *PointDamageEvent->HitInfo.BoneName.ToString());
			CurrentHP -= DamageAmount;
		}

		if (CurrentHP <= 0)
		{
			CurrentHP = 0;
			CurrentState = EZombieState::DEAD;
			CurrentAnimState = EZombieAnimState::DEATH;
			
			AFPS_ZombieAIControll* AIC = Cast<AFPS_ZombieAIControll>(GetController());
			if (AIC)
			{
				AIC->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);
			}

			//GetMesh()->SetSimulatePhysics(true);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			UE_LOG(LogClass, Warning, TEXT("죽음"));
			//DisableInput()
		}
	}
	else if (DamageEvent.IsOfType(FDamageEvent::ClassID))
	{

	}
	return 0.0f;
}

