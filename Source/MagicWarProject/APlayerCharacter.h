// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "APlayerCharacter.generated.h"

UCLASS()
class MAGICWARPROJECT_API AAPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAPlayerCharacter();

	UFUNCTION(Client, Reliable)
		void ClientRPC();

	UFUNCTION(Server, Reliable)
		void ServerShootRPC();

	UFUNCTION(NetMulticast, Reliable)
		void NetMulticastShootRPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DistSpawnBullet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int numberSkin;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USkeletalMesh*> skins;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();
	void TakeDamage();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void CameraRotation(float Axis);
};
