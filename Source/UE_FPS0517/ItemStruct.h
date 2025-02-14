// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStruct.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknown = 0		UMETA(Display = "Unknown"),
	Comsume = 1		UMETA(Display = "Comsume"),
	Equip = 2		UMETA(Display = "Equip"),
};

UENUM(BlueprintType)
enum class EEqipSlot : uint8
{
	NotUse			= 0		UMETA(Display = "NotUse"),
	WeaponRightHand = 1		UMETA(Display = "WeaponRightHand"),
	Weapon			= 2		UMETA(Display = "Weapon"),
	WeaponBack01	= 3		UMETA(Display = "WeaponBack01"),
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct UE_FPS0517_API FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//ItemIndex	ItemName	ItemType	ItemEquipSlot	ItemFloat01	ItemCount	ItemThumnail	ItemMesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EEqipSlot ItemEquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float ItemFloat01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int  ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TAssetPtr<class UTexture2D>  ItemThumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TAssetPtr<class UMeshComponent>  ItemMesh;
	
};
