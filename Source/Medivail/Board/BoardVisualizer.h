// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Core/MedivailPlayerState.h"
#include "../Core/MedivailGameState.h"
#include "BoardVisualizer.generated.h"


class ACreatureVisual;
class BoardTypes;

UCLASS()
class MEDIVAIL_API ABoardVisualizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardVisualizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TMap<int32, FVector> SlotPosition;

	void BuildSlotLookup();
	int32 MakeSlotKey(bool bIsPlayerSide, int32 Row, int32 Lane);

	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	TSubclassOf<ACreatureVisual> CreatureVisualClass;

	UPROPERTY()
	TMap<int32, TObjectPtr<ACreatureVisual>> SpawnedVisuals;

	UPROPERTY()
	TObjectPtr<AMedivailGameState> GS;

	UPROPERTY()
	TObjectPtr<AMedivailPlayerState> PS;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	UFUNCTION()
	void HandleSlotOccupied(bool bIsPlayerSide, int32 Row, int32 Lane);

	UFUNCTION()
	void HandleSlotCleared(bool bIsPlayerSide, int32 Row, int32 Lane);

	UFUNCTION()
	void HandlePhaseChanged(ETurnPhase NewPhase, ETurnPhase OldPhase);

	UFUNCTION()
	void HandleHandChanged();

	void UpdateHandLayout();

};
