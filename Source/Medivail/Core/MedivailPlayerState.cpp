// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailPlayerState.h"
#include "../Cards/CardDataAsset.h"


void AMedivailPlayerState::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MedivailPlayerState BeginPlay"));

	for (UCardDataAsset* Card : TestDeckCards) {
		if (Card) {
			FCardInstance NewInstance;
			NewInstance.CardAsset = Card;
			Hand.Add(NewInstance);
			OnHandChanged.Broadcast();
			UE_LOG(LogTemp, Error, TEXT("Hand Size : %d"), Hand.Num());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Card does not exist"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Card 1: %s, Card 2: %s"), *Hand[0].CardAsset->DisplayName.ToString(), *Hand[1].CardAsset->DisplayName.ToString());
}

void AMedivailPlayerState::DrawCard(){
	OnHandChanged.Broadcast();
	return;
}

