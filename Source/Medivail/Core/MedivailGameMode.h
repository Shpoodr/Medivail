// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Creatures/CreatureDataAsset.h"
#include "MedivailGameState.h"
#include "MedivailGameMode.generated.h"//must be bottom include

/**
 * 
 */
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
	virtual void BeginPlay() override;
	void ResolveCombat();
};
