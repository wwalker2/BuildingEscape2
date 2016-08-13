// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "NewBuildingEscapeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEWBUILDINGESCAPE_API ANewBuildingEscapeGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	/** Called when the game starts. */
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Items")
	int32 numOfItems = 0;
	


};
