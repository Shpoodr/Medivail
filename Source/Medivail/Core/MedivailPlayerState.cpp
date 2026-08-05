// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailPlayerState.h"

void AMedivailPlayerState::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MedivailPlayerState BeginPlay"));
}