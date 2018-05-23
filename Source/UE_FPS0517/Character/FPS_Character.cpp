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
	FStringClassReference Anim_Male_Ref(TEXT("AnimBlueprint'/Game/BluePrints/Anumations/ABP_FPSAnimation.ABP_FPSAnimation_C'"));
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
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
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
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFPS_Character::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFPS_Character::UnSprint);
	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Pressed, this, &AFPS_Character::LookAround);
	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Released, this, &AFPS_Character::UndoLookAround);
	PlayerInputComponent->BindAction(TEXT("Prone"), IE_Pressed, this, &AFPS_Character::DoProne);
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
	if (CanCrouch() && !bIsSprint)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AFPS_Character::Tryironsight()
{
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
	if (!bIsCrouched && !bIsIronsight && GetCharacterMovement()->Velocity.Size() > 0 && !bIsProne)
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



