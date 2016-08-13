// Fill out your copyright notice in the Description page of Project Settings.

#include "NewBuildingEscape.h"
#include "NewBuildingEscapeGameMode.h"

void ANewBuildingEscapeGameMode::BeginPlay() {
	Super::BeginPlay();
	numOfItems = FMath::RandRange(1, 3);
}


