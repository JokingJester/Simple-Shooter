// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"


void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT("Pawn Is Killed"));
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}