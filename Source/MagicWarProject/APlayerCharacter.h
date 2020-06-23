// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponMagic.h"
#include "DamageableComponent.h"
#include "APlayerCharacter.generated.h"

UCLASS()
class MAGICWARPROJECT_API AAPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAPlayerCharacter();

	UFUNCTION(Client, Reliable)
		void ClientShoot();

	UFUNCTION(Server, Reliable)
		void ServerShoot();

	UFUNCTION(NetMulticast, Reliable)
		void NetMulticastShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AWeaponMagic* CurrentWeapon;

// 	UPROPERTY(BlueprintReadWrite, EditAnywhere)
// 		int numberSkin;

// 	UPROPERTY(BlueprintReadWrite, EditAnywhere)
// 		TArray<USkeletalMesh*> skins;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDamageableComponent* Damageable;

	void CallShoot();
	void Shoot();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void CameraRotation(float Axis);
};
