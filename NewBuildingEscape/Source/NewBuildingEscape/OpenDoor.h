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

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key1 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Keys")
		AActor* Key3 = nullptr;

	AActor* Owner = nullptr;

	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(EditAnywhere)
		float TriggerMass = 30.f;

	TMap<FString, bool> MakeAList();

	bool ItemOnPlate1();

	bool ItemOnPlate2();

	bool Unlocked1 = false;
	bool Unlocked2 = false;

	int32 numOfItems = 0;
	
};
