// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardVisualizer.h"
#include "kismet/GameplayStatics.h"
#include "../Core/MedivailGameState.h"
#include "../Creatures/CreatureVisual.h"
#include "BoardSlotMarker.h"

// Sets default values
ABoardVisualizer::ABoardVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABoardVisualizer::BeginPlay()
{
	Super::BeginPlay();

	BuildSlotLookup();

	GS = GetWorld()->GetGameState<AMedivailGameState>();

	if (ensure(GS)) {
		GS->OnSlotOccupied.AddDynamic(this, &ABoardVisualizer::HandleSlotOccupied);
		GS->OnSlotCleared.AddDynamic(this, &ABoardVisualizer::HandleSlotCleared);
	}

	
}

// Called every frame
void ABoardVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoardVisualizer::BuildSlotLookup() {
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

int32 ABoardVisualizer::MakeSlotKey(bool bIsPlayerSide, int32 Row, int32 Lane) {
	int32 Key = (bIsPlayerSide ? 0 : 1) * 100 + (Row * 10) + Lane;
	UE_LOG(LogTemp, Warning, TEXT("Key Value : %d"), Key);
	return Key;
}

void ABoardVisualizer::HandleSlotOccupied(bool bIsPlayerSide, int32 Row, int32 Lane) {
	int32 Key = MakeSlotKey(bIsPlayerSide, Row, Lane);
	FVector* Position = SlotPosition.Find(Key);

	if (Position) {
		ACreatureVisual* Visual = GetWorld()->SpawnActor<ACreatureVisual>(CreatureVisualClass, *Position, FRotator::ZeroRotator);
		if (Visual) {
			Visual->InitializeVisual(GS->GetSlot(bIsPlayerSide, Row, Lane)->Occupant, Row, Lane, bIsPlayerSide);
			SpawnedVisuals.Add(Key, Visual);
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("Slot Occupuied: side %d, row %d, lane %d"), bIsPlayerSide, Row, Lane);
}

void ABoardVisualizer::HandleSlotCleared(bool bIsPlayerSide, int32 Row, int32 Lane) {
	int32 Key = MakeSlotKey(bIsPlayerSide, Row, Lane);

	if (ACreatureVisual* Visual = SpawnedVisuals.FindRef(Key)) {
		Visual->Destroy();
		SpawnedVisuals.Remove(Key);
	}

	UE_LOG(LogTemp, Warning, TEXT("Slot Cleared: side %d, row %d, lane %d"), bIsPlayerSide, Row, Lane);
}

void ABoardVisualizer::HandlePhaseChanged(ETurnPhase NewPhase, ETurnPhase OldPhase) {
	//this is for later use
	return;
}