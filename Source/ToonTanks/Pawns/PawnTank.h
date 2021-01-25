// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "PawnTank.generated.h"
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public ABase
{
	GENERATED_BODY()

	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) USpringArmComponent* SpringArm;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) UCameraComponent* Camera;

		FVector MoveDirection;
		FQuat TurnDirection;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true")) float MoveSpeed = 100.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true")) float TurnSpeed = 100.f;

		APlayerController* PlayerController;
		bool bIsPlayerAlive = true;

		void CalculateMoveInput(float Value);
		void CalculateRotationInput(float Value);

		void Move();
		void Rotate();

	public:
		APawnTank();
		// Called every frame
		virtual void Tick(float DeltaTime) override;  
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		virtual void HandleDestruction() override;
		bool IsPlayerAlive() {
			return bIsPlayerAlive;
		}

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		
};
