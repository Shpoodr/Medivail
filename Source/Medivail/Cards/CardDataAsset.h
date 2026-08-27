// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class MEDIVAIL_API UCardDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Card")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Card")
	int32 InkCost = 1;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Card")
	TObjectPtr<UTexture2D> CardArt;
};
