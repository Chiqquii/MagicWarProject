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

// 	FVector Dir = GetActorForwardVector() * 2 * GetWorld()->GetDeltaSeconds();
// 
// 	SetActorLocation(GetActorLocation() * Dir);

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

