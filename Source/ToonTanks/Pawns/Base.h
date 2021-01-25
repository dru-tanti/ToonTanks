// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Base.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API ABase : public APawn
{
	GENERATED_BODY()

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) USceneComponent* ProjectileSpawnPoint;
	
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true")) TSubclassOf<AProjectileBase> Projectile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true")) UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, Category = "Effects") UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects") USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects") TSubclassOf<UMatineeCameraShake> DeathShake;

public:
	// Sets default values for this pawn's properties
	ABase();

protected:
	void RotateTurret(FVector LookTarget);
	void Fire();
	virtual void HandleDestruction();

};
