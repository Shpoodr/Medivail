// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MedivailGameState.h"
#include "MedivailGameMode.generated.h"//must be bottom include

/**
 * 
 */
class ABoardVisualizer;
//class AMedivailGameState;
class UCreatureDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSlotOccupied, bool, bIsPlayerSide, int32, Row, int32, Lane);

UCLASS()
class MEDIVAIL_API AMedivailGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	TObjectPtr<UCreatureDataAsset> TestCreature1;
	
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	TObjectPtr<UCreatureDataAsset> TestCreature2;


public:
	AMedivailGameMode();

protected:
	UPROPERTY()
	TObjectPtr<AMedivailGameState> MedivailGS;

	UPROPERTY()
	TObjectPtr<ABoardVisualizer> BoardVS;

	virtual void BeginPlay() override;
	void ResolveCombat();

};

