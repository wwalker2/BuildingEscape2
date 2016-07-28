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
	/*numOfItems = FMath::RandRange(1, 3);*/
	numOfItems = 1;
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

	if (ItemOnPlate() == true) {
		OnOpen.Broadcast();
	}

	else {
		OnClose.Broadcast();
	}
}

bool UOpenDoor::ItemOnPlate()
{
	switch (numOfItems) {
	case 1:
		return Item1();
		//break;
	case 2:
		return Items2();
		//break;
	case 3:
		return false;
		//break;
	default:
		return false;
		//break;
	}
}

bool UOpenDoor::Item1()
{
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		if (OverlappingActors[0]->GetName().Equals(winList[0]->GetName())) {
			Unlocked1 = true;
			UE_LOG(LogTemp, Warning, TEXT("The needed item is %s"), *winList[0]->GetName());
		}
	}

	return Unlocked1;
}

bool UOpenDoor::Items2()
{
	bool result = false;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	

	while (OverlappingActors.Num() < numOfItems) {
		if (OverlappingActors.Contains(winList[0])) {
			Unlocked1 = true;
			UE_LOG(LogTemp, Warning, TEXT("%s is on the point."), *winList[0]->GetName());
		}
		if (OverlappingActors.Contains(winList[1])) {
			Unlocked2 = true;
			UE_LOG(LogTemp, Warning, TEXT("%s is on the point."), *winList[1]->GetName());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("There are not enough items."));
		}
	}

	if (Unlocked1 == true && Unlocked2 == true) {
		result = true;
	}

	return result;
}

void UOpenDoor::fillWinList()
{
	int i = 0;
	while(winList.Num() < numOfItems) {
		int32 select = FMath::RandRange(0, 2);
		winList.AddUnique(itemsList[select]);
		UE_LOG(LogTemp, Warning, TEXT("%s is a Win Item"), *winList[i]->GetName());
		i++;
	}
}