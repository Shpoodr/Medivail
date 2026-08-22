// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MedivailPlayerController.h"

void AMedivailPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Click Begin Play test"));
	bShowMouseCursor = true;

	UE_LOG(LogTemp, Warning, TEXT("PC is: %s"), *GetClass()->GetName());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		if (GameplayContext) {
			Subsystem->AddMappingContext(GameplayContext, 0);
		}
	}
}

void AMedivailPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent Test"));
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent)) {
		
		//click action
		if (ClickAction) {
			EIC->BindAction(ClickAction, ETriggerEvent::Started, this, &AMedivailPlayerController::HandleClick);
		}


	}
}

void AMedivailPlayerController::HandleClick() {
	UE_LOG(LogTemp, Warning, TEXT("Click Handled"));
}