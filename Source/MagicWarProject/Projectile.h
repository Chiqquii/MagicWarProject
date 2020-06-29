// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "DamageableComponent.h"
#include "PointsComponent.h"
#include "APlayerCharacter.h"
#include "Projectile.generated.h"

UCLASS()
class MAGICWARPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TimeLife;

	float _TimerLife;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UParticleSystem* ParticleHit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyBullet();

	UFUNCTION(BlueprintCallable)
		void HitBullet(UPrimitiveComponent* OverlappedComp, AActor* OtherActor);

	UPROPERTY(EditAnywhere, Replicated)
		class AAPlayerCharacter* Character;
};
