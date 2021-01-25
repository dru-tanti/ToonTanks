// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh")); // Setting a required component
	// Dynamic Binding of a function. Function it calls needs to be a UFUNCTION()
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	RootComponent = ProjectileMesh; // Setting the root component of the actor.
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Momement"));
	Projectile->InitialSpeed = MovementSpeed; // Setting the values of a component.
	Projectile->MaxSpeed = MovementSpeed; // Setting the values of a component.

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>("Trail Emitter");
	TrailParticle->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay() {
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AActor* MyOwner = GetOwner();
	if (!MyOwner) return;
	// Checking that we didn't collide with ourselves.
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
		Destroy();
	}

}

