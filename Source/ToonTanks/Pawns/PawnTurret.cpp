// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay() {
    Super::BeginPlay();
    Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (!Player || DistanceToPlayer() > FireRange) return;

    RotateTurret(Player->GetActorLocation());
}

void APawnTurret::CheckFireCondition() {
    if (!Player || !Player->IsPlayerAlive()) return;
    if (DistanceToPlayer() <= FireRange) {
        Fire();
    }
}

float APawnTurret::DistanceToPlayer() {
    if (!Player) return 0.f;
    return FVector::Dist(Player->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction() {
    Super::HandleDestruction();
    Destroy();
}