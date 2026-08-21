// Fill out your copyright notice in the Description page of Project Settings.


#include "MedivailGameMode.h"
#include "MedivailPlayerState.h"
#include "../Board/BoardSlotMarker.h"
#include "../Board/BoardVisualizer.h"
#include "../Creatures/CreatureDataAsset.h"
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
	//BuildSlotLookup();
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

void AMedivailGameMode::AdvancePhase() {
	switch (MedivailGS->CurrentPhase) {
	case ETurnPhase::Placement:
		UE_LOG(LogTemp, Warning, TEXT("Phase was: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		MedivailGS->SetPhase(ETurnPhase::Resolution);
		UE_LOG(LogTemp, Warning, TEXT("New Phase is: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		ResolveCombat();
		break;
		
	case ETurnPhase::Resolution:
		UE_LOG(LogTemp, Warning, TEXT("Phase was: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		MedivailGS->SetPhase(ETurnPhase::CleanUp);
		UE_LOG(LogTemp, Warning, TEXT("New Phase is: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		//clear deaths, refresh ink, check win con
		break;

	case ETurnPhase::CleanUp:
		UE_LOG(LogTemp, Warning, TEXT("Phase was: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		MedivailGS->SetPhase(ETurnPhase::Placement);
		UE_LOG(LogTemp, Warning, TEXT("New Phase is: %s"), *UEnum::GetValueAsString(MedivailGS->CurrentPhase));
		break;
	}
}

void AMedivailGameMode::DebugAdvancePhase() {
	AdvancePhase();
}