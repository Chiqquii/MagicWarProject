// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponMagic.h"
#include "Unit.h"
#include "Net/UnrealNetwork.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MAGICWARPROJECT_API AEnemyCharacter : public AUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(Server, Reliable)
		void ServerShootRPC(AWeaponMagic* CurrentWeapon, AActor* Actor);

	UFUNCTION(Server, Reliable)
		void GetTargetServerRPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, EditDefaultsOnly)
	class AUnit* Target;

	UPROPERTY(EditDefaultsOnly)
		float CounterShoot;

	UPROPERTY(EditDefaultsOnly)
		float RequiredDistanceToTarget;

	UPROPERTY(EditDefaultsOnly)
		float DistanceToCurrentTarget;

	UPROPERTY(EditDefaultsOnly)
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

	UFUNCTION()
		void Shoot(AWeaponMagic* CurrentWeapon, AActor* Actor);

};
