// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* Player;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetNumberOfTurrets();

public:
	void ActorDied(AActor* DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop") int32 StartDelay = 3;

	virtual void BeginPlay() override;

	// UFUNCTION(BlueprintImplementableEvent) = Does not need a code implementation as they will be impemented in Blueprints.
	UFUNCTION(BlueprintImplementableEvent) void GameStart(); 
	UFUNCTION(BlueprintImplementableEvent) void GameOver(bool PlayerWon);
};
