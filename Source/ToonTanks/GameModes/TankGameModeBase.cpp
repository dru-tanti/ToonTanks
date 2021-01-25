// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

#define OUT // Marks values as out parameters. I.E. A function will define these paramenters

void ATankGameModeBase::BeginPlay() {
	Super::BeginPlay();
	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {
	// if(DeadActor == Player) HandleGameOver(false);
	if (DeadActor == Player) {
		Player->HandleDestruction();
		HandleGameOver(false);
		if(PlayerControllerRef) {
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	} else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
		DestroyedTurret->HandleDestruction();
		if (--TargetTurrets <= 0) HandleGameOver(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("Pawn was killed!"));
}

void ATankGameModeBase::HandleGameStart() {
	TargetTurrets = GetNumberOfTurrets();
	Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();
	if(PlayerControllerRef) {
		PlayerControllerRef->SetPlayerEnableState(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) {
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetNumberOfTurrets() {
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT TurretActors);
	return TurretActors.Num();
}