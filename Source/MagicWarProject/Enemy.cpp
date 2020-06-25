// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	 NextPathPoint = PathToTarget();
	 MoveSpeed = 50;
	 RequiredDistanceToTarget = 300;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (NextPathPoint - GetActorLocation()).Size();

	//Si la distancia es menor que busque otro path para seguir, si la distancia es maor que se mueva porque todavia no llego a la distancia para disparar
	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = PathToTarget();
	}
	else
	{
		FVector Dir = NextPathPoint - GetActorLocation();
		FVector Location = GetActorLocation();
		Location += Dir * MoveSpeed * DeltaTime;
		SetActorLocation(Location);
	}

}

FVector AEnemy::PathToTarget()
{
	//Provisorio: Agarro al player
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);

	//El path que va a seguir por el navmesh
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);

	//Si losp untos para ir hacia el objetivo que devuelva el segundo de la lista porque el primero es su pos actual
	if (NavPath->PathPoints.Num() > 1)
	{
		return NavPath->PathPoints[1];
	}

	//Si no tiene mas de uno que devuelva su pos
	return GetActorLocation();
}

void AEnemy::Damage(float damage)
{

}

void AEnemy::Kill()
{

}
