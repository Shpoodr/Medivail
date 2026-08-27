// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Cards/CardDataAsset.h"
#include "CreatureDataAsset.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class MEDIVAIL_API UCreatureDataAsset : public UCardDataAsset
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
	int32 BaseAttack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
	int32 BaseHealth = 1;
};
