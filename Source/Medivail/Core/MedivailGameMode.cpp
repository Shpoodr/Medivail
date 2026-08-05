// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailGameMode.h"
#include "MedivailPlayerState.h"

AMedivailGameMode::AMedivailGameMode() {
	GameStateClass = AMedivailGameState::StaticClass();
	PlayerStateClass = AMedivailPlayerState::StaticClass();
	MedivailGS = GetGameState<AMedivailGameState>();
}
	
void AMedivailGameMode::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("MediVailGameMode BeginPlay"));
	UE_LOG(LogTemp, Warning, TEXT("GameState is: %s"), *GetWorld()->GetGameState()->GetClass()->GetName());
	MedivailGS->InitializeBoard();

	MedivailGS->PlacementHandling(TestCreature1, true, 1, 1);
	MedivailGS->PlacementHandling(TestCreature2, false, 1, 1);
	MedivailGS->PlacementHandling(TestCreature2, false, 5, 7);

	MedivailGS->LogDump();
}

void AMedivailGameMode::ResolveCombat() {
	TArray<FBoardSlot*> PlayerSlots = MedivailGS->GetOccupiedSlots(true);
	TArray<FBoardSlot*> EnemySlots = MedivailGS->GetOccupiedSlots(false);
	TArray<FBoardSlot*> DeadSlots;

	if (PlayerSlots.Num() > 0) {
		for (FBoardSlot* Slot : PlayerSlots) {
			FBoardSlot* Target = MedivailGS->FindTarget(*Slot);
			if (Target != nullptr) {
				bool IsDead = MedivailGS->HandleAttack(*Target, Slot->Occupant->BaseAttack);
				if (IsDead) DeadSlots.AddUnique(Target);
			}
		}
	}

	if (EnemySlots.Num() > 0) {
		for (FBoardSlot* Slot : EnemySlots) {
			FBoardSlot* Target = MedivailGS->FindTarget(*Slot);
			if (Target != nullptr) {
				bool IsDead = MedivailGS->HandleAttack(*Target, Slot->Occupant->BaseAttack);
				if (IsDead) DeadSlots.AddUnique(Target);
			}
		}
	}

	if (DeadSlots.Num() > 0) {
		for (FBoardSlot* Slot : DeadSlots) {
			MedivailGS->HandleDeath(*Slot);
		}
	}
}