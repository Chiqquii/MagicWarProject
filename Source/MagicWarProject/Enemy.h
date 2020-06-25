// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamageable.h"
#include "APlayerCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class MAGICWARPROJECT_API AEnemy : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly)
	float RequiredDistanceToTarget;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector PathToTarget();
	void Damage(float damage);
	void Kill();
};
