// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_Character.generated.h"

UCLASS()
class UE_FPS0517_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Weapon;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* Weapon;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPawnNoiseEmitterComponent* Noise;

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void Turn(float Value);

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
	void TryCrouch();

	UFUNCTION()
	void Tryironsight();

	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void UnSprint();

	UFUNCTION()
	void DoProne();

	UFUNCTION()
	void LookAround();

	UFUNCTION()
	void StartFire();

	UFUNCTION()
	void StopFire();

	UFUNCTION()
	void UndoLookAround();
	
	FRotator GetAimOffset() const;

	UFUNCTION()
	void OnShot();

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void ViewItemTooltip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsIronsight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsSprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsLook = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsProne = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsProning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		bool bIsFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FVector ProneSpringArmPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FVector NormalSpringArmPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FVector CrouchSpringArmPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float WalkSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float JogSpeed = 360.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float SprintSpeed = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float ProneSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float FullHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		UAnimMontage* DeadAnimation;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		class UParticleSystem* Explosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		class UParticleSystem* HitExplosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		class UParticleSystem* HitBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		class USoundBase* ExplosionSound;
	

	FTimerHandle TimerHandle;

	TArray<class AMasterItems*> CanPickupList;

	//UFUNCTION(BlueprintCallable)
	//	void AddPickupItemList(class AMasterITems* Item);

	//UFUNCTION(BlueprintCallable)
	//	void RemovePickupItemList(class AMasterITems* Item);
};
