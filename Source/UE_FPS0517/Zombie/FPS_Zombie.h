// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_Zombie.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	NORMAL	UMETA(Display = "Normal"),
	BATTLE	UMETA(Display = "Battle"),
	DEAD	UMETA(Display = "Dead"),
	CHASE	UMETA(Display = "Chase"),
};

UENUM(BlueprintType)
enum class EZombieAnimState : uint8
{
	IDLE		UMETA(Display = "IDLE"),
	WALK		UMETA(Display = "WALK"),
	ATTACK01	UMETA(Display = "ATTACK01"),
	ATTACK02	UMETA(Display = "ATTACK02"),
	DEATH		UMETA(Display = "DEATH"),
	SCREAM		UMETA(Display = "SCREAM"),
	RUN			UMETA(Display = "RUN"),
};


UCLASS()
class UE_FPS0517_API AFPS_Zombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Zombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float CurrentHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float walkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float runSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float AttackRange = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float Attack = 30.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool Hit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		EZombieState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		EZombieAnimState CurrentAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* Behaviortree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<class AFPS_ZombieTargetPoint*>  PatrolPoints;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnHearNoise(APawn* InPawn, const FVector & Location, float Volme);

	void OnAttack();
};
