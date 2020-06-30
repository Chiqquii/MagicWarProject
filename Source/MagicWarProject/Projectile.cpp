// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Templates/SubclassOf.h"
#include "Net/UnrealNetwork.h"
#include "Logging/LogMacros.h"

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

void AProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectile, Character);

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
		damageable->Damage(Damage);
		//HitDamageServerRPC(Damage, damageable);


	if (Character && Character->Points)
	{
		auto points = OtherActor->FindComponentByClass<UPointsComponent>();

		if (points)
		{
			Character->Points->AddPoints(points->PointsToGive);
		}
	}


	DestroyBullet();
}

void AProjectile::HitDamageServerRPC_Implementation(float HitDamage, UDamageableComponent* HitDamageable)
{
	FString fstringVar = HitDamageable->GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("000 HIT DAMAGE, %s"), *fstringVar);
	HitDamageable->Damage(HitDamage);
}

