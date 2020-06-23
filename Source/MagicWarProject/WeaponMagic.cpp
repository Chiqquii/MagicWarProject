// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponMagic.h"

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

void AWeaponMagic::Fire(AAPlayerCharacter* character)
{
	if (character)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		character->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		if (ProjectileClass != NULL) 
		{
			GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation() + character->GetActorForwardVector() * DistSpawnBullet, character->GetActorRotation());
		}
	}
}

// Called every frame
void AWeaponMagic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

