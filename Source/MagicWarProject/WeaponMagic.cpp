// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponMagic.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWeaponMagic::AWeaponMagic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AWeaponMagic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponMagic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	UE_LOG(LogTemp, Warning, TEXT("ProjectileClass"));
	DOREPLIFETIME(AWeaponMagic, ProjectileClass);
}

void AWeaponMagic::Fire(AAPlayerCharacter* character)
{
	if (character)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		character->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		if (ProjectileClass != nullptr) 
		{
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation() + character->GetActorForwardVector() * DistSpawnBullet, character->GetActorRotation());
			
			if(Projectile)
				Projectile->Character = character;
		}
	}
}

void AWeaponMagic::FireActor(AActor* Actor)
{
	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnPROJECTILEClass"));
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation() + Actor->GetActorForwardVector() * DistSpawnBullet, UKismetMathLibrary::MakeRotFromXZ(Actor->GetActorForwardVector(), GetActorUpVector()));
	}
}

// Called every frame
void AWeaponMagic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

