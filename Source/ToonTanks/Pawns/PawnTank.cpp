// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank() {
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
    Super::BeginPlay();
    PlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Rotation should be calculated first since it could affect the direction the actor moves in.
    Rotate();
    Move();
    if (PlayerController) {
        FHitResult Hit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
        FVector HitLocation = Hit.ImpactPoint;
        RotateTurret(HitLocation);
    }
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Setting delegates to handle the input events.
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value) {
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotationInput(float Value) {
    float RotateAmount = Value * TurnSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    TurnDirection = FQuat(Rotation);
}

void APawnTank::Move() {
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate() {
    AddActorLocalRotation(TurnDirection, true);
}

void APawnTank::OnDestroy() {
    Super::OnDestroy();
}