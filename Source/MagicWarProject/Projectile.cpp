// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	Location += GetActorForwardVector() * Speed * DeltaTime;

	SetActorLocation(Location);

	_TimerLife += DeltaTime;

	if (_TimerLife >= TimeLife)
		DestroyBullet();
}

void AProjectile::DestroyBullet() 
{
	Destroy(true);
}

void AProjectile::HitBullet(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleHit, GetActorLocation(), FRotator::ZeroRotator, true);

	DestroyBullet();
}

