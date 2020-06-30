// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "APlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyCharacter, Target);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetTargetServerRPC();
	RequiredDistanceToTarget = 300;
	DistanceToCurrentTarget = 0;
	CanMove = true;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target != NULL) 
	{
		DistanceToCurrentTarget = (GetActorLocation() - Target->GetActorLocation()).Size();

		FVector forward = Target->GetActorLocation() - GetActorLocation();
		FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(forward, GetActorUpVector());
		SetActorRotation(Rot);
	}

	if (CanMove)
	{
		if (DistanceToCurrentTarget > RequiredDistanceToTarget)
		{
			FVector Dir = Target->GetActorLocation() - GetActorLocation();
			FVector Location = GetActorLocation();

			Location += Dir * MoveSpeed * DeltaTime;

			SetActorLocation(Location);
		}
		else
		{
			CanMove = false;
		}
	}
	else
	{
		if (DistanceToCurrentTarget > StartChasingPlayer)
			CanMove = true;
		else if (Weapon)
		{
			CounterShoot += GetWorld()->GetDeltaSeconds();

			if (CounterShoot >= DelayShoot) 
			{
				CounterShoot = 0;
				ServerShootRPC(Weapon, this);
			}
		}
	}
}


void AEnemyCharacter::GetTargetServerRPC_Implementation()
{
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPlayerCharacter::StaticClass(), AllPlayers);


	float DistanceToTarget = NULL;
	AActor* CurrentTarget = nullptr;

	for (AActor* Actor : AllPlayers)
	{
		if (DistanceToTarget == NULL)
		{
			DistanceToTarget = (Actor->GetActorLocation() - GetActorLocation()).Size();
			CurrentTarget = Actor;
		}
		else
		{
			float CurrentActorDistance = (Actor->GetActorLocation() - GetActorLocation()).Size();
			if (DistanceToTarget > CurrentActorDistance)
			{
				DistanceToTarget = CurrentActorDistance;
				CurrentTarget = Actor;
			}
		}
	}

	Target = CurrentTarget;
}



void AEnemyCharacter::ServerShootRPC_Implementation(AWeaponMagic* CurrentWeapon, AActor* Actor)
{
	Shoot(CurrentWeapon, Actor);
}

void AEnemyCharacter::Shoot(AWeaponMagic* CurrentWeapon, AActor* Actor)
{
	CurrentWeapon->FireActor(Actor);
}

