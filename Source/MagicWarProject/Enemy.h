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

	AActor* Target;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float RequiredDistanceToTarget;

	float DistanceToCurrentTarget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	AActor* GetTarget();
	void Damage(float damage);
	void Kill();
};
