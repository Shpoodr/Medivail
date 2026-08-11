// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailGameMode.h"
#include "MedivailPlayerState.h"
#include "../Board/BoardSlotMarker.h"
#include "Kismet/GameplayStatics.h"

AMedivailGameMode::AMedivailGameMode() {
	GameStateClass = AMedivailGameState::StaticClass();
	PlayerStateClass = AMedivailPlayerState::StaticClass();
}
	
void AMedivailGameMode::BeginPlay() {
	Super::BeginPlay();

	MedivailGS = GetGameState<AMedivailGameState>();

	UE_LOG(LogTemp, Warning, TEXT("MediVailGameMode BeginPlay"));
	UE_LOG(LogTemp, Warning, TEXT("GameState is: %s"), *GetWorld()->GetGameState()->GetClass()->GetName());

	if (ensure(MedivailGS)) {
		MedivailGS->InitializeBoard();
	}
	
	MedivailGS->PlacementHandling(TestCreature1, true, 1, 1);
	MedivailGS->PlacementHandling(TestCreature2, false, 1, 1);
	MedivailGS->PlacementHandling(TestCreature2, false, 5, 7);

	//MedivailGS->LogDump();
	BuildSlotLookup();
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

void AMedivailGameMode::BuildSlotLookup() {
	TArray<AActor*> FoundMarkers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoardSlotMarker::StaticClass(), FoundMarkers);
	for (int32 i = 0; i < FoundMarkers.Num(); i++) {
		ABoardSlotMarker* Marker = Cast<ABoardSlotMarker>(FoundMarkers[i]);
		if (Marker) {
			SlotPosition.Add(MakeSlotKey(Marker->bIsPlayerSide, Marker->Row, Marker->Lane), Marker->GetActorLocation());
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Found %d markers"), FoundMarkers.Num());

	for (const TPair<int32, FVector>& Pair : SlotPosition) {
		UE_LOG(LogTemp, Warning, TEXT("Slot Key %d at %s"), Pair.Key, *Pair.Value.ToString());
	}

	if (SlotPosition.Num() != 16) {
		UE_LOG(LogTemp, Warning, TEXT("Slot Positions != 16"));
	}
}

int32 AMedivailGameMode::MakeSlotKey(bool bIsPlayerSide, int32 Row, int32 Lane) {
	int32 Key = (bIsPlayerSide ? 0 : 1) * 100 + (Row * 10) + Lane;
	UE_LOG(LogTemp, Warning, TEXT("Key Value : %d"), Key);
	return Key;
}
