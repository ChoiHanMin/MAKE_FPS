// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h" // 플레이어 컨트롤 
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Engine/StaticMesh.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShake.h"
#include "FPS_BulletDamageType.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"

#include "Character/WeaponComponent.h"


// Sets default values
AFPS_Character::AFPS_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringAram"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->bUsePawnControlRotation = true;

	SpringArm->SetRelativeLocation(FVector(0, 30, 70));
	SpringArm->TargetArmLength = 150.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Male(TEXT("SkeletalMesh'/Game/Male_Grunt/Mesh/male_grunt.male_grunt'"));
	if (SK_Male.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Male.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	bUseControllerRotationPitch = false;

	// AnimationSetting.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// BeginPlay 가능.
	FStringClassReference Anim_Male_Ref(TEXT("AnimBlueprint'/Game/BluePrints/Animations/ABP_FPSAnimation.ABP_FPSAnimation_C'"));
	if (UClass* Anim_Male_Class = Anim_Male_Ref.TryLoadClass<UAnimInstance>())
	{
		GetMesh()->SetAnimInstanceClass(Anim_Male_Class);
	}

	// 생성자에서만.
	//static ConstructorHelpers::FClassFinder<UAnimInstance> Anim(TEXT("AnimBlueprint'/Game/BluewPrints/Anumations/ABP_FPSAnimation.ABP_FPSAnimation_C'"));
	//if (Anim.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(Anim.Class);
	//}

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("RHandWeapon"));

	/*Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("RHandWeapon"));*/

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_M4A1(TEXT("StaticMesh'/Game/Weapons/M4A1/SM_M4A1.SM_M4A1'"));
	if (SK_M4A1.Succeeded())
	{
		Weapon->SetStaticMesh(SK_M4A1.Object);
	}

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	GetCharacterMovement()->MaxWalkSpeedCrouched = WalkSpeed;


	NormalSpringArmPosition = SpringArm->GetRelativeTransform().GetLocation();
	CrouchSpringArmPosition = FVector(NormalSpringArmPosition.X, NormalSpringArmPosition.Y, NormalSpringArmPosition.Z - 40);
	ProneSpringArmPosition = FVector(130, NormalSpringArmPosition.Y, NormalSpringArmPosition.Z - 100);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Explosion(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	if (P_Explosion.Succeeded())
	{
		Explosion = P_Explosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitExplosion(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	if (P_HitExplosion.Succeeded())
	{
		HitExplosion = P_HitExplosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> S_Explosion(TEXT("SoundCue'/Game/Sound/Weapons/SMG_Thompson/Cue_Thompson_Shot.Cue_Thompson_Shot'"));
	if (S_Explosion.Succeeded())
	{
		ExplosionSound = S_Explosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim_Dead(TEXT("AnimMontage'/Game/Male_Grunt/Animations/Death_2_Montage.Death_2_Montage'"));
	if (Anim_Dead.Succeeded())
	{
		DeadAnimation = Anim_Dead.Object;
	}

}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	CurrentHP = FullHP;
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogClass, Warning, TEXT("%f"), SpringArm->GetComponentLocation().Z);

	if (bIsSprint&&GetCharacterMovement()->Velocity.SizeSquared() == 0)
	{
		bIsSprint = false;
	}
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPS_Character::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPS_Character::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPS_Character::LookUp);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AFPS_Character::TryCrouch);
	PlayerInputComponent->BindAction(TEXT("ironsight"), IE_Pressed, this, &AFPS_Character::Tryironsight);
	PlayerInputComponent->BindAction(TEXT("Prone"), IE_Pressed, this, &AFPS_Character::DoProne);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFPS_Character::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFPS_Character::UnSprint);

	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Pressed, this, &AFPS_Character::LookAround);
	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Released, this, &AFPS_Character::UndoLookAround);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AFPS_Character::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AFPS_Character::StopFire);
}

void AFPS_Character::MoveRight(float Value)
{
	if (Value != 0.0f && !bIsSprint)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPS_Character::MoveForward(float Value)
{
	if (Value != 0.0f && !bIsProning)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void AFPS_Character::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}
void AFPS_Character::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AFPS_Character::TryCrouch()
{
	if (bIsProning)
	{
		return;
	}

	if (CanCrouch() && !bIsSprint && !bIsProne)
	{
		Crouch();
	}
	else if (bIsProne)
	{
		bIsProne = false;
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AFPS_Character::Tryironsight()
{
	if (bIsSprint)
	{
		return;
	}
	//bIsIronsight = bIsIronsight ? false : true;
	if (!bIsIronsight && !bIsSprint)
	{
		bIsIronsight = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else if (bIsIronsight && !bIsSprint)
	{
		bIsIronsight = false;
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}
}

void AFPS_Character::Sprint()
{
	if (!bIsCrouched && !bIsIronsight && GetCharacterMovement()->Velocity.Size() > 0 && !bIsProne && !bIsFire)
	{
		bIsSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AFPS_Character::UnSprint()
{
	if (bIsSprint)
	{
		bIsSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}
}

void AFPS_Character::DoProne()
{
	if (!bIsProne && !bIsSprint)
	{
		bIsProne = true;
		UnCrouch();
		GetCharacterMovement()->MaxWalkSpeed = ProneSpeed;
	}
	else if (bIsProne && !bIsSprint)
	{
		bIsProne = false;
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		UnCrouch();
	}
}

void AFPS_Character::LookAround()
{
	if (!bIsIronsight)
	{
		bIsLook = true;
		bUseControllerRotationYaw = false;
	}
}

void AFPS_Character::StartFire()
{
	if (!bIsSprint && !bIsProning)
	{
		bIsFire = true;
		OnShot();
	}
}

void AFPS_Character::StopFire()
{
	if (bIsFire)
	{
		bIsFire = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AFPS_Character::UndoLookAround()
{
	if (bIsLook)
	{
		bIsLook = false;
		bUseControllerRotationYaw = true;
	}
}

FRotator AFPS_Character::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}



void AFPS_Character::OnShot()
{
	if (!bIsFire)
	{
		return;
	}

	FVector CameraLocation;
	FRotator CameraRotation;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	FVector WorldLocation;
	FVector WorldDirection;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, WorldLocation, WorldDirection);

	FVector TraceStart = CameraLocation;
	//	Zombie->GetActorLocation()
	FVector TraceEnd = CameraLocation + (WorldDirection*80000.0f);
	//	Zombie->GetActorLocation() + (WorldDirection*8000.0f);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreObjects; // 팀킬 할지 안할지 선택.
	FHitResult OutHit;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	IgnoreObjects.Add(this);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, Weapon->GetSocketTransform(TEXT("Flame")), true);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, Weapon->GetSocketTransform(TEXT("Flame")).GetLocation());

	// 광선 추적 시작
	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectTypes, false, IgnoreObjects, EDrawDebugTrace::None, OutHit, true, FLinearColor::Blue, FLinearColor::Red, 5.0f);

	if (Result)
	{
		TraceStart = Weapon->GetSocketTransform(TEXT("Flame")).GetLocation();
		FVector Dir = OutHit.Location - TraceStart;
		TraceEnd = TraceStart + (Dir *2.0f);

		bool Hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectTypes, false, IgnoreObjects, EDrawDebugTrace::None, OutHit, true, FLinearColor::Black, FLinearColor::Green, 5.0f);
		if (Hit)
		{

			// 기본 데미지
			//UGameplayStatics::ApplyDamage(OutHit.GetActor(), 30.0f, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UFPS_BulletDamageType::StaticClass());

			// 반경데미지
			//UGameplayStatics::ApplyRadialDamage(GetWorld(), 30.f, OutHit.ImpactPoint, 300.0f, UFPS_BulletDamageType::StaticClass(), IgnoreObjects, this, UGameplayStatics::GetPlayerController(GetWorld(), 0), true);

			// 포인트 데미지
			UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), 30.0f, TraceEnd - TraceStart, OutHit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UFPS_BulletDamageType::StaticClass());

			// 맞은 이펙트
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitExplosion, OutHit.Location, FRotator::ZeroRotator);
		}
	}
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->PlayCameraShake(UCameraShake::StaticClass());

	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch += 1.0f;
	CurrentRotation.Yaw += FMath::RandRange(-0.5f, 0.5f);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(CurrentRotation);

	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPS_Character::OnShot, 0.2f);

	}
}

float AFPS_Character::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP <= 0)
	{
		return 0;
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
			UE_LOG(LogClass, Warning, TEXT("머리 읔 %s"), *PointDamageEvent->HitInfo.BoneName.ToString());
			CurrentHP = 0;
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("읔 %s"), *PointDamageEvent->HitInfo.BoneName.ToString());
			CurrentHP -= DamageAmount;
		}

		if (CurrentHP <= 0)
		{
			CurrentHP = 0;
			//GetMesh()->SetSimulatePhysics(true);
			PlayAnimMontage(DeadAnimation);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//DisableInput()

			
		}
	}
	else if (DamageEvent.IsOfType(FDamageEvent::ClassID))
	{

	}
	return 0.0f;
}

