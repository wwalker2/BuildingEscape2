// Fill out your copyright notice in the Description page of Project Settings.

#include "NewBuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
	}
	numOfItems = FMath::RandRange(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("%d is the random number"), numOfItems);

	itemsList.Add(Key1);
	itemsList.Add(Key2);
	itemsList.Add(Key3);

	fillWinList();
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ItemOnPlate1() == true) {
		OnOpen.Broadcast();
	}

	else {
		OnClose.Broadcast();
	}
}

bool UOpenDoor::ItemOnPlate1()
{
	bool result = false;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		int32 j = 0;
		if (OverlappingActors[0]->GetName().Equals(winList[j]->GetName())) {
			Unlocked1 = true;
			UE_LOG(LogTemp, Warning, TEXT("The needed item is %s"), *winList[j]->GetName());
			j++;
			if (OverlappingActors[0]->GetName().Equals(winList[j]->GetName())) {
				Unlocked2 = true;
				UE_LOG(LogTemp, Warning, TEXT("The next item is %s"), *winList[j]->GetName());
			}
		}
	}
	if (Unlocked1 == true && Unlocked2 == true) {
		result = true;
	}
	return result;
}

bool UOpenDoor::ItemOnPlate2()
{
	TArray<AActor*> OverlappingActors;
	PressurePlate2->GetOverlappingActors(OUT OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		if (OverlappingActors[0]->GetName().Equals(Key1->GetName())) {
			Unlocked2 = true;
			UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate 2"), *Key1->GetName());
		}
	}
	return Unlocked2;
}

void UOpenDoor::fillWinList()
{
	while(winList.Num() < numOfItems) {
		int32 select = FMath::RandRange(0, 2);
		winList.AddUnique(itemsList[select]);
		UE_LOG(LogTemp, Warning, TEXT("%s is a Win Item"), *winList[0]->GetName());
	}
}