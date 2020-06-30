// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageableComponent.h"
#include "PointsComponent.h"
#include "RespawnComponent.h"
#include "Unit.generated.h"

UCLASS()
class MAGICWARPROJECT_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Replicated)
		class UDamageableComponent* Damageable;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Replicated)
		class UPointsComponent* Points;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Replicated)
		class URespawnComponent* Respawn;

	UFUNCTION(BlueprintImplementableEvent)
		void ViewDeath();

	UFUNCTION(BlueprintImplementableEvent)
		void ViewRespawn();

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool DeathUnit;
};
