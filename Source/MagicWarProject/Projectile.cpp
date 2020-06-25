// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Templates/SubclassOf.h"

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

void AProjectile::HitBullet(UPrimitiveComponent* OverlappedComp, AActor* OtherActor) 
{
	auto damageable = OtherActor->FindComponentByClass<UDamageableComponent>();


	if (damageable) 
	{
		damageable->Damage(Damage);
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HIT!"));

	if (Character && Character->Points && Character->Points->IgnoreAddPoints != false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Points hit"));
		auto points = OtherActor->FindComponentByClass<UPointsComponent>();

		if (points)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Add points"));
			Character->Points->AddPoints(points->PointsToGive);
		}
	}


	DestroyBullet();
}

