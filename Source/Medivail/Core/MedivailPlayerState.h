// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MedivailPlayerState.generated.h"//must be bottom include

/**
 * 
 */

class UCardDataAsset;

USTRUCT(BlueprintType)
struct FCardInstance {
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UCardDataAsset>CardAsset;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandChanged);

UCLASS()
class MEDIVAIL_API AMedivailPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Hand")
	FOnHandChanged OnHandChanged;


protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FCardInstance> Hand;

	UPROPERTY()
	TArray<FCardInstance> Deck;

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	TArray<TObjectPtr<UCardDataAsset>> TestDeckCards;

	void DrawCard();

};
