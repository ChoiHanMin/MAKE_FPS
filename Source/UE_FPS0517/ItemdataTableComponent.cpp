// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemdataTableComponent.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UItemdataTableComponent::UItemdataTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemData(TEXT("DataTable'/Game/Data/ItemTable.ItemTable'"));
	if (DT_ItemData.Succeeded())
	{
		dataTable = DT_ItemData.Object;
	}
}


// Called when the game starts
void UItemdataTableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemdataTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStruct& UItemdataTableComponent::GetItemData(int ItemIndex)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	return *dataTable->FindRow<FItemStruct>(*FString::FromInt(ItemIndex), TEXT("ItemIndex"));
}

