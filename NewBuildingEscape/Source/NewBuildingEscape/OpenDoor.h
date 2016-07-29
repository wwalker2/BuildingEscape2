// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWBUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

	int32 numOfItems = 0;

	TArray<AActor*> itemsList;
	TArray<AActor*> winList;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key1 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key3 = nullptr;

	AActor* Owner = nullptr;

	//Handles what happens when items touch the spotlight.
	bool ItemOnPlate();

	//Returns true when the specified number of items are on the spot.
	bool Item1();
	bool Items2();
	bool Items3();

	//Returns true if the specified key is on the spot.
	bool Unlocked1 = false;
	bool Unlocked2 = false;
	bool Unlocked3 = false;

	//Fills the winList TArray.
	void fillWinList();
};
