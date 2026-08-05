// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MedivailPlayerState.generated.h"//must be bottom include

/**
 * 
 */
UCLASS()
class MEDIVAIL_API AMedivailPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
