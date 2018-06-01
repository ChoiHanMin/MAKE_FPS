// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterItems.h"
#include "Components/SphereComponent.h"
#include "ItemdataTableComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StreamableManager.h"
#include "Components/StaticMeshComponent.h"
#include "Character/FPS_Character.h"



AMasterItems::AMasterItems()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetStaticMeshComponent());
	Sphere->SetSphereRadius(200.0f);
	Sphere->bGenerateOverlapEvents = true;

	GetStaticMeshComponent()->SetupAttachment(Sphere);

	ItemDataTable = CreateDefaultSubobject<UItemdataTableComponent>(TEXT("ItemdataTable"));
}

void AMasterItems::BeginPlay()
{
	Super::BeginPlay();

	if (ItemDataTable&&ItemDataTable->dataTable)
	{
		ItemIndex = FMath::RandRange(1, 6) * 10;
		FItemStruct Data = ItemDataTable->GetItemData(ItemIndex);

		FStreamableManager  AsstLoader;
//		GetStaticMeshComponent()->SetStaticMesh(AsstLoader.LoadSynchronous<UStaticMesh>(Data.ItemMesh));
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMasterItems::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &AMasterItems::OnEndOverlap);
	}
}

//void AMasterItems::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if (OtherActor->ActorHasTag(TEXT("Player")))
//	{
//		AFPS_Character* Pawn = Cast<AFPS_Character>(OtherActor);
//		if (Pawn)
//		{
//			Pawn->AddPickupItemList(this);
//		}
//	}
//}
//
//void AMasterItems::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor->ActorHasTag(TEXT("Player")))
//	{
//		AFPS_Character* Pawn = Cast<AFPS_Character>(OtherActor);
//		if (Pawn)
//		{
//			Pawn->RemovePickupItemList(this);
//		}
//	}
//}