// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponMagic.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MAGICWARPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	AActor* Target;

	UPROPERTY()
		float CounterShoot;

	UPROPERTY(EditDefaultsOnly)
		float RequiredDistanceToTarget;

	float DistanceToCurrentTarget;

	bool CanMove;

	UPROPERTY(EditDefaultsOnly)
	float StartChasingPlayer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AWeaponMagic* Weapon;

	UPROPERTY(EditAnywhere)
		float DelayShoot;

	AActor* GetTarget();
	void Damage(float damage);
	void Kill();
	void Shoot();

};
