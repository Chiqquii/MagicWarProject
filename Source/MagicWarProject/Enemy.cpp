// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/Actor.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Target = GetTarget();
	RequiredDistanceToTarget = 300;
	DistanceToCurrentTarget = 0;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target != NULL)
		DistanceToCurrentTarget = (GetActorLocation() - Target->GetActorLocation()).Size();

	if (DistanceToCurrentTarget > RequiredDistanceToTarget)
	{
		FVector Dir = Target->GetActorLocation() - GetActorLocation();
		FVector Location = GetActorLocation();

		Location += Dir * MoveSpeed * DeltaTime;

		SetActorLocation(Location);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("LLEGUE"))
	}

}

AActor* AEnemy::GetTarget()
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

	return CurrentTarget;
}

void AEnemy::Damage(float damage)
{

}

void AEnemy::Kill()
{

}
