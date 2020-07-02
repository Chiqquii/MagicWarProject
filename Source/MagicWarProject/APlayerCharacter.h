// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.h"
#include "WeaponMagic.h"
#include "DamageableComponent.h"
#include "PointsComponent.h"
#include "RespawnComponent.h"
#include "APlayerCharacter.generated.h"

UCLASS()
class MAGICWARPROJECT_API AAPlayerCharacter : public AUnit
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAPlayerCharacter();

	UFUNCTION(Server, Reliable)
		void ServerShoot(AAPlayerCharacter* Character);

	UFUNCTION(NetMulticast, Reliable)
		void NetMulticastShoot();

	UFUNCTION(NetMulticast, Reliable)
		void WinNetMulticastRPC(int Record);

	UFUNCTION(NetMulticast, Reliable)
		void GameOverNetMulticastRPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AWeaponMagic* CurrentWeapon;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CallShoot(AAPlayerCharacter* Character);
	void Shoot(AAPlayerCharacter* Character);
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void CameraRotation(float Axis);

	UFUNCTION(BlueprintImplementableEvent)
	void ViewAttack();

	UFUNCTION(BlueprintImplementableEvent)
		void ViewGameOver();

	UFUNCTION(BlueprintImplementableEvent)
		void ViewWin(int Record);
};
