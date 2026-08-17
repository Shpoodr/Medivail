// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailGameState.h"
#include "../Creatures/CreatureDataAsset.h"

void AMedivailGameState::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MediVailGameState BeginPlay"));
}

void AMedivailGameState::InitializeBoard() {
	const int32 NumRows = 2;
	const int32 NumLanes = 4;

	PlayerSideBoard.SetNum(NumRows);
	EnemySideBoard.SetNum(NumRows);

	InitializeSide(PlayerSideBoard, true, NumLanes);
	InitializeSide(EnemySideBoard, false, NumLanes);
} 

void AMedivailGameState::InitializeSide(TArray<FBoardRow>& Board, bool bIsPlayer, int32 Lanes) {
	for (int32 r = 0; r < Board.Num(); r++) {
		Board[r].Slots.SetNum(Lanes);
		for (int32 l = 0; l < Board[r].Slots.Num(); l++) {
			Board[r].Slots[l].bIsAPlayerSide = bIsPlayer;
			Board[r].Slots[l].Row = r;
			Board[r].Slots[l].Lane = l;
		}
	}
}

FBoardSlot* AMedivailGameState::GetSlot(bool bPlayerSide, int32 Row, int32 Lane) {
	TArray<FBoardRow>& Board = bPlayerSide ? PlayerSideBoard : EnemySideBoard;

	if (!Board.IsValidIndex(Row) || !Board[Row].Slots.IsValidIndex(Lane)) {
		return nullptr;
	}

	return &Board[Row].Slots[Lane];
}

bool AMedivailGameState::PlacementHandling(UCreatureDataAsset* Creature, bool bPlayerSide, int32 Row, int32 Lane) {
	if (FBoardSlot* Slot = GetSlot(bPlayerSide, Row, Lane)) {
		if (Slot->IsEmpty()) {
			Slot->Occupant = Creature;
			Slot->CurrentHealth = Creature->BaseHealth;
			OnSlotOccupied.Broadcast(bPlayerSide, Row, Lane);
			UE_LOG(LogTemp, Warning, TEXT("CREATURE PLACED"));
			return true;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("SLOT NOT EMPTY"));
			return false;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SLOT = NULLPTR"));
		return false;
	}

}

void AMedivailGameState::LogDump() {
	TArray<FBoardRow>& PlayerBoard = PlayerSideBoard;
	TArray<FBoardRow>& EnemyBoard = EnemySideBoard;
	for (int32 i = 0; i < PlayerBoard.Num(); i++) {
		for (int32 z = 0; z < PlayerBoard[i].Slots.Num(); z++) {
			if (PlayerBoard[i].Slots[z].IsEmpty()) {
				UE_LOG(LogTemp, Warning, TEXT("[Player], Row %d, Lane %d: Empty"), i, z);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("[Player], Row %d, Lane %d: %s HP: %d"),
				i, z, *PlayerBoard[i].Slots[z].Occupant->DisplayName.ToString(), PlayerBoard[i].Slots[z].CurrentHealth);
			}

			if (EnemyBoard[i].Slots[z].IsEmpty()) {
				UE_LOG(LogTemp, Warning, TEXT("[Enemy], Row %d, Lane %d: Empty"), i, z);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("[Enemy], Row %d, Lane %d: %s HP: %d"),
				i, z, *EnemyBoard[i].Slots[z].Occupant->DisplayName.ToString(), EnemyBoard[i].Slots[z].CurrentHealth);
			}
		}
	}
}

bool AMedivailGameState::HandleAttack(FBoardSlot& Slot, int32 AttackDmg) {
	if (Slot.IsEmpty()) return false;
	Slot.CurrentHealth -= AttackDmg;

	return Slot.CurrentHealth <= 0;
}

void AMedivailGameState::HandleDeath(FBoardSlot& Slot) {
	Slot.CurrentHealth = 0;
	Slot.Occupant = nullptr;
	OnSlotCleared.Broadcast(Slot.bIsAPlayerSide, Slot.Row, Slot.Lane);
}

FBoardSlot* AMedivailGameState::FindTarget(FBoardSlot& Attacker) {
	if (Attacker.IsEmpty()) return nullptr;
	TArray<FBoardRow>& Board = Attacker.bIsAPlayerSide ? EnemySideBoard : PlayerSideBoard;
	FBoardSlot* Slot = nullptr;

	if (!Board[0].Slots[Attacker.Lane].IsEmpty()) {
		Slot = &Board[0].Slots[Attacker.Lane];
		return Slot;
	}
	else if (!Board[1].Slots[Attacker.Lane].IsEmpty()) {
		Slot = &Board[1].Slots[Attacker.Lane];
		return Slot;
	}
	else {
		//do Damage to player
		return nullptr;
	}
}

TArray<FBoardSlot*> AMedivailGameState::GetOccupiedSlots(bool bPlayerSide) {
	TArray<FBoardRow>& Board = bPlayerSide ? PlayerSideBoard : EnemySideBoard;
	TArray<FBoardSlot*> OccupiedSlots;

	for (int32 r = 0; r < Board.Num(); r++) {
		for (int32 l = 0; l < Board[r].Slots.Num(); l++) {
			if (!Board[r].Slots[l].IsEmpty()) {
				OccupiedSlots.Add(&Board[r].Slots[l]);
			}
		}
	}
	return OccupiedSlots;
}
