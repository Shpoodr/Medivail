// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "../Board/BoardTypes.h"
#include "MedivailGameState.generated.h" //must be bottom include


/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSlotOccupied, bool, bIsPlayerSide, int32, Row, int32, Lane);

UCLASS()
class MEDIVAIL_API AMedivailGameState : public AGameStateBase
{
	GENERATED_BODY()

public: 
	UPROPERTY(BlueprintReadOnly, Category = "Board")
	TArray<FBoardRow> PlayerSideBoard;

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	TArray<FBoardRow> EnemySideBoard;

	FBoardSlot* GetSlot(bool bPlayerSide, int32 Row, int32 Lane);

	void InitializeBoard();
	void InitializeSide(TArray<FBoardRow>& board, bool bPlayerSide, int32 Lanes);
	bool PlacementHandling(UCreatureDataAsset* Creature, bool bPlayerSide, int32 Row, int32 Lane);
	void LogDump();
	bool HandleAttack(FBoardSlot&, int32 AttackDmg);
	void HandleDeath(FBoardSlot& Slot);
	FBoardSlot* FindTarget(FBoardSlot& Slot);
	TArray<FBoardSlot*> GetOccupiedSlots(bool bPlayerSide);

	UPROPERTY(BlueprintAssignable, Category= "Board")
	FOnSlotOccupied OnSlotOccupied;

	UPROPERTY(BlueprintAssignable, Category = "Board")
	FOnSlotOccupied OnSlotCleared;

protected:
	virtual void BeginPlay() override;
};
