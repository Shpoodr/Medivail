#pragma once

#include "CoreMinimal.h"
#include "BoardTypes.generated.h"//must be bottom include

class UCreatureDataAsset;

USTRUCT(BlueprintType)
struct FBoardSlot {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	TObjectPtr<UCreatureDataAsset>Occupant = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	int32 CurrentHealth = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Board")
	int32 Row = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	int32 Lane = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	bool bIsAPlayerSide = false;

	bool IsEmpty() const { return Occupant == nullptr; }
};

USTRUCT(BlueprintType)
struct FBoardRow{ //Row 0 = Front Row 1 = Back

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Board")
	TArray<FBoardSlot> Slots;
};